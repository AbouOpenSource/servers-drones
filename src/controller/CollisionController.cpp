//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "CollisionController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneConfigChangeEvent.hpp"
#include "../core/event/internal/CollisionDetectEvent.hpp"

std::string CollisionController::SERVICE = "CollisionService";

CollisionController::CollisionController()
    : Controller(CollisionController::SERVICE)
{
    event_manager_->subscribe(EventType::DRONE_CONFIG_CHANGED, [this] (Event* e, auto&) {
        drones_ = ((DroneConfigChangeEvent*)e)->get_drones();
    });

    event_manager_->subscribe(EventType::FRAME_UPDATED, [this] (Event* e, auto&) {
        if (!drones_.empty()) {
            for(auto* drone : drones_) {
                prevent_collision_for_drone(drone);
            }
        }
    });
}

void CollisionController::prevent_collision_for_drone(Drone *drone)
{
    Circle zone = get_zone_for_drone(drone);
    for (auto* drone_bis : drones_) {
        Circle zone_bis = get_zone_for_drone(drone_bis);
        if (drone != drone_bis){
            if (zone.touch_with(&zone_bis)) {
                event_manager_->publish(EventType::COLLISION_DETECTED, new CollisionDetectEvent(drone, drone_bis));
            }
        }
    }
}

Circle CollisionController::get_zone_for_drone(Drone* drone)
{
    auto& drone_position = drone->get_position();
    Position center = Position(drone_position.x_, drone_position.y_);
    return {center, COLLISION_RADIUS};
}
