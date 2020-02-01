//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#include "ZoneController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneConfigChangeEvent.hpp"
#include "../core/event/internal/DroneZoneChangeEvent.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"
#include "../core/event/internal/DroneTargetChangeEvent.hpp"
#include "../core/event/internal/DeleteDroneEvent.hpp"
#include "../util/VectorUtil.hpp"

std::string ZoneController::SERVICE = "ZoneService";

ZoneController::ZoneController()
    : Controller(ZoneController::SERVICE)
{
    event_manager_->subscribe(EventType::FRAME_UPDATED, [this] (Event* e, auto&) {
        calculate_drones_distribution();
        track_drone_zone_change();
    });

    event_manager_->subscribe(EventType::DRONE_DELETED, [this] (Event* e, auto&) {
        remove_drone_from_server(((DeleteDroneEvent*)e)->get_drone(), nullptr);
    });

    event_manager_->subscribe(EventType::DRONE_CONFIG_CHANGED, [this] (Event* e, auto&) {
        drones_ = ((DroneConfigChangeEvent*)e)->get_drones();
    });

    event_manager_->subscribe(EventType::DIAGRAM_CHANGED, [this] (Event* e, auto&) {
        diagram_controller_ = ((DiagramChangeEvent*)e)->get_diagram_controller();
        find_neighbors();
    });
}

void ZoneController::add_drone_to_server(Drone *drone, Server* server)
{
    for (auto* it: server_data_[server]->drones) {
        if (it == drone) {
            return;
        }
    }
    server_data_[server]->drones.push_back(drone);
}

void ZoneController::remove_drone_from_server(Drone *drone, Server* server)
{
    ServerData* data;
    for (auto& s_it: server_data_) {
        if (s_it.first == server) {
            continue;
        }
        data = get_server_data(s_it.first);
        auto d_it = data->drones.begin();
        while (d_it != data->drones.end()) {
            if ((*d_it)->get_id() == drone->get_id()) {
                std::cout << "REMOVING" << std::endl;
                get_server_data(s_it.first)->drones.erase(d_it);
            }
        }
    }
}

void ZoneController::track_drone_zone_change()
{
    auto& polygons = diagram_controller_->get_polygons();
    Polygon* polygon;
    Server* server;
    for (auto* drone: drones_) {
        int i(0);
        do {
            polygon = polygons[i];
            server = diagram_controller_->get_server_for_polygon(polygons[i]);
            if (polygon->is_inside(drone->get_position())) {
                find_unfilled_neighbor(drone, server);
                if (drone->get_server_name() != server->get_name()) {
                    event_manager_->publish(EventType::DRONE_CHANGED_ZONE, new DroneZoneChangeEvent(drone, server, polygon));
                    add_drone_to_server(drone, server);
                    remove_drone_from_server(drone, server);
                    break;
                }
            }
            i++;
        } while (i < diagram_controller_->get_servers().size());
    }
}

void ZoneController::find_unfilled_neighbor(Drone *drone, Server* server)
{
    auto* data = get_server_data(server);
    if (!is_server_full(server)) {
        send_target_event(drone, server);
    } else {
        int i(0);
        Server* target = data->neighbors[i];
        while (is_server_full(target) && i < data->neighbors.size()) {
            i++;
            target = data->neighbors[i];
        }
        std::cout << "Moving D(" << drone->get_id() << ") to " << target->get_name() << std::endl;
        send_target_event(drone, target);
    }
}

void ZoneController::calculate_drones_distribution()
{
    for (auto* server: diagram_controller_->get_servers()) {
        float expected =
                (diagram_controller_->get_server_area(server) * 1000000 * drones_.size() / diagram_controller_->get_total_area());
        get_server_data(server)->expected = expected;
    }
}

ZoneController::ServerData *ZoneController::get_server_data(Server *server)
{
    if (!server_data_[server]) {
        server_data_[server] = new ServerData{0, {}, {}};
    }
    return server_data_[server];
}

void ZoneController::find_neighbors()
{
    auto servers = diagram_controller_->get_servers();
    for (auto* server: servers) {
        for (auto* server_bis: servers) {
            if (server == server_bis) {
                continue;
            }
            if (diagram_controller_->are_polygons_neighbors(
                    diagram_controller_->get_polygon_for_server(server),
                    diagram_controller_->get_polygon_for_server(server_bis)
            )) {
                get_server_data(server)->neighbors.push_back(server_bis);
            }
        }
    }
}

bool ZoneController::is_server_full(Server *server)
{
    auto* data = get_server_data(server);
    return data->expected == data->drones.size();
}

void ZoneController::send_target_event(Drone *drone, Server *server)
{
    event_manager_->publish(EventType::DRONE_CHANGED_TARGET, new DroneTargetChangeEvent(drone, server));
}
