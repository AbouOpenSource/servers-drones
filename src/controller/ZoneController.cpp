//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#include "ZoneController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneConfigChangeEvent.hpp"
#include "../core/event/internal/DroneChangeZoneEvent.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"

std::string ZoneController::SERVICE = "ZoneService";

ZoneController::ZoneController()
    : Controller(ZoneController::SERVICE)
{
    event_manager_->subscribe(EventType::FRAME_UPDATED, [this] (Event* e, const EventManager::EventDetail& detail) {
        if (!drones_.empty()) {
            for (auto* drone: drones_) {
                track_drone_zone_change(drone);
            }
        }
    });

    event_manager_->subscribe(EventType::DRONE_CONFIG_CHANGED, [this] (Event* e, const EventManager::EventDetail& detail) {
        drones_ = ((DroneConfigChangeEvent*)e)->get_drones();
    });

    event_manager_->subscribe(EventType::DIAGRAM_CHANGED, [this] (Event* e, const EventManager::EventDetail& detail) {
        diagram_controller_ = ((DiagramChangeEvent*)e)->get_diagram_controller();
        for (auto* server: diagram_controller_->get_servers()) {
            server_drones_[server] = {};
        }
    });
}

void ZoneController::track_drone_zone_change(Drone *drone)
{
    auto& polygons = diagram_controller_->get_polygons();
    auto& drone_position = drone->get_position();
    Polygon* polygon;
    Server* server;
    int i(0);
    do {
        polygon = polygons[i];
        server = diagram_controller_->get_server_for_polygon(polygons[i]);
        if (polygon->is_inside(drone->get_position())) {
            if (drone->get_server_name() != server->get_name()) {
                event_manager_->publish(EventType::DRONE_CHANGED_ZONE, new DroneChangeZoneEvent(drone, server, polygon));
                break;
            }
        }
        i++;
    } while (i < diagram_controller_->get_servers().size());
}
