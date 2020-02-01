//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#include "ZoneController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneConfigChangeEvent.hpp"
#include "../core/event/internal/DroneZoneChangeEvent.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"
#include "../core/event/internal/DroneTargetChangeEvent.hpp"

std::string ZoneController::SERVICE = "ZoneService";

ZoneController::ZoneController()
    : Controller(ZoneController::SERVICE)
{
    event_manager_->subscribe(EventType::FRAME_UPDATED, [this] (Event* e, auto&) {
        calculate_drones_distribution();
        track_drone_zone_change();
        check_drones_distribution();
        monitor_drones();
    });

    event_manager_->subscribe(EventType::DRONE_CONFIG_CHANGED, [this] (Event* e, auto&) {
        drones_ = ((DroneConfigChangeEvent*)e)->get_drones();
    });

    event_manager_->subscribe(EventType::DIAGRAM_CHANGED, [this] (Event* e, auto&) {
        diagram_controller_ = ((DiagramChangeEvent*)e)->get_diagram_controller();
        find_neighbors();
    });
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

void ZoneController::check_drones_distribution()
{
    int drone_count(0);
    for (auto* server: diagram_controller_->get_servers()) {
        drone_count = 0;
        for (auto* drone: drones_) {
            if (diagram_controller_->get_polygon_for_server(server)->is_inside(drone->get_position())) {
                drone_count++;
            }
        }
        get_server_data(server)->current = drone_count;
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
                if (drone->get_server_name() != server->get_name()) {
                    event_manager_->publish(EventType::DRONE_CHANGED_ZONE, new DroneZoneChangeEvent(drone, server, polygon));
                    break;
                }
            }
            i++;
        } while (i < diagram_controller_->get_servers().size());
    }
}

void ZoneController::monitor_drones()
{
    for (auto* drone: drones_) {
        Server* main;
        for (auto* server: diagram_controller_->get_servers()) {
            if (diagram_controller_->get_polygon_for_server(server)->is_inside(drone->get_position())) {
                main = server;
                break;
            }
        }
        Server* next = main;
        for (auto* neighbor: get_server_data(main)->neighbors) {
            if (compare(next, neighbor)) {
                next = neighbor;
            }
        }
        event_manager_->publish(EventType::DRONE_CHANGED_TARGET, new DroneTargetChangeEvent(drone, next));
    }
}

bool ZoneController::compare(Server *server, Server* neighbor) {
    auto* server_data = get_server_data(server);
    auto* neighbor_data = get_server_data(neighbor);

    return neighbor_data->expected > server_data->expected && (float)neighbor_data->current < neighbor_data->expected;
}

void ZoneController::calculate_drones_distribution()
{
    for (auto* server: diagram_controller_->get_servers()) {
        float expected =
                (diagram_controller_->get_server_area(server) * 1000000 * drones_.size()) / diagram_controller_->get_total_area();
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
