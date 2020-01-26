//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "CollisionController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/service/ServiceContainer.hpp"

std::string CollisionController::SERVICE = "CollisionService";

CollisionController::CollisionController()
    : ServiceProvider(CollisionController::SERVICE)
{
    ServiceContainer *service_container = ServiceContainer::get_instance();
    window_ = (Window *) service_container->get_service(Window::SERVICE);
    direction_controller_ = (DirectionController *) service_container->get_service(DirectionController::SERVICE);
    server_controller_ = (ServerController *) service_container->get_service(ServerController::SERVICE);
    EventManager::Subscription subscription = [this] (Event* e, const TypeUtil::Callback& unsubscribe) {
        for(auto & drone : get_drones()) {
            //prevent_collision_for_drone(&drone);
            //monitor_trajectory_of_drone(&drone);
        }
    };
    auto* event_manager = (EventManager *) service_container->get_service(EventManager::SERVICE);
    event_manager->subscribe(EventType::FRAME_UPDATE, subscription);
}

void CollisionController::prevent_collision_for_drone(Drone *drone)
{
    Circle zone = get_zone_for_drone(drone);
    for(auto& drone_bis : get_drones()) {
        Circle zone_bis = get_zone_for_drone(&drone_bis);
        if (zone.touch_with(&zone_bis)) {
            direction_controller_->prevent_collision_between_drones(drone, &drone_bis);
        }
    }
}

void CollisionController::monitor_trajectory_of_drone(Drone *drone)
{
    auto* drone_move = direction_controller_->get_instant_movement_for_drone(drone);
    auto& drone_position = drone->get_position();

    if(abs(drone_position.y_ - window_->getWindowHeight()) < 100 && drone_move->speed.y_ > 0){
        drone_move->acceleration.y_ = -drone_move->acceleration.y_;
        drone_move->acceleration.x_ = -drone_move->acceleration.x_;
        drone_move->speed.y_ = -drone_move->speed.y_;
    }

    if(drone_position.y_ < 10 && drone_move->speed.y_ < 0){
        drone_move->acceleration.y_ = -drone_move->acceleration.y_;
        drone_move->acceleration.x_ = -drone_move->acceleration.x_;
        drone_move->speed.y_ = -drone_move->speed.y_;
    }
    
    if(drone_position.x_ < 10 && drone_move->speed.x_ < 0){
        drone_move->acceleration.y_ = -drone_move->acceleration.y_;
        drone_move->acceleration.x_ = -drone_move->acceleration.x_;
        drone_move->speed.x_ = -drone_move->speed.x_;
    }
    
    if(abs(drone_position.x_ - window_->getWindowWidth()) < 100 && drone_move->speed.x_ > 0){
        drone_move->acceleration.y_ = -drone_move->acceleration.y_;
        drone_move->acceleration.x_ = -drone_move->acceleration.x_;
        drone_move->speed.x_ = -drone_move->speed.x_;
    }
}

Circle CollisionController::get_zone_for_drone(Drone* drone) const
{
    Position center = Position(drone->get_position().x_, drone->get_position().y_);
    return {center, COLLISION_RADIUS};
}

std::vector<Drone> &CollisionController::get_drones()
{
    return server_controller_->drones();
}
