//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "DirectionController.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"


std::string DirectionController::SERVICE = "DirectionService";

DirectionController::DirectionController()
    : ServiceProvider(DirectionController::SERVICE),
      callbacks_({})
{
    auto* event_manager = (EventManager *) ServiceContainer::get_instance()->get_service(EventManager::SERVICE);
    EventManager::Subscription subscription = [this] (Event* e, const TypeUtil::Callback& unsubscribe) {
        for(auto & it : callbacks_) {
            it.second();
        }
    };
    event_manager->subscribe(EventType::FRAME_UPDATE, subscription);
}

void DirectionController::set_drone_target(Drone *drone, const Vector2D &target)
{
    auto& move = drone->get_move_data();

    move.target = target;

    Vector2D& drone_position = drone->get_position();

    callbacks_[drone] = [this, drone, &move, &drone_position] () {
        std::cout<<"Position x : "<<drone_position.x_<<std::endl;
        std::cout<<"Position y : "<<drone_position.x_<<std::endl;

        move.dx = (move.target.x_ - drone_position.x_);
        move.dy = (move.target.y_ - drone_position.y_);
        move.distance = sqrt(move.dx * move.dx + move.dy * move.dy);
        move.dx/=move.distance;
        move.dy/=move.distance;
        move.dx*=20;
        move.dy*=20;

         //move.target_reached = move.distance > 60;

        if (!move.circular_mode && move.target_reached) {
            move.circular_mode = true;
        }

        update_forces_of_drone(drone);
        update_acceleration_of_drone(drone);
        update_speed_of_drone(drone);
        update_position_of_drone(drone);

    };
}

void DirectionController::prevent_collision_between_drones(Drone *d1, Drone *d2)
{
    auto& move = d1->get_move_data();

    auto& d1_pos = d1->get_position();
    auto& d2_pos = d2->get_position();
    std::cout<<"D1 " << d1_pos<<std::endl;
    std::cout<<"D2 " << d2_pos<<std::endl;

    //TODO define the force to avoid the collison with the drone passing in args
    float distance = get_distance_between_drones(d1, d2);

    Vector2D ba =  Vector2D(d1_pos.x_ - d2_pos.x_, d1_pos.y_ - d2_pos.y_);

    if (distance < 48) {
        Vector2D force_ba = MAX_FORCE * (ba / distance);
        move.forces = force_ba;
        update_forces_of_drone(d1);
        update_acceleration_of_drone(d1);
        update_speed_of_drone(d1);

    } else if (distance < 96) {
        Vector2D force_ba = ((distance - 96) / (48 - 96)) * (MAX_FORCE * (ba / distance));
        move.forces = force_ba;
        update_forces_of_drone(d1);
        update_acceleration_of_drone(d1);
        update_speed_of_drone(d1);
    }
}

float DirectionController::get_distance_between_drones(Drone *d1, Drone *d2) const
{
    auto& d1_pos = d1->get_position();
    auto& d2_pos = d2->get_position();
    return sqrt(
            (d2_pos.x_ - d1_pos.x_) * (d2_pos.x_ - d1_pos.x_)
            +
            (d2_pos.y_ - d1_pos.y_) * (d2_pos.y_ - d1_pos.y_)
    );
}

void DirectionController::update_acceleration_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
     if (move.target_reached) {
         // Acceleration for circular movement
         move.theta_zero = 0;
         move.radius = 100;
         move.acceleration.x_ = (-move.radius) * (move.w * move.w) * cos(move.w * move.temps + move.theta_zero);
         move.acceleration.y_ = (-move.radius) * (move.w * move.w) * sin(move.w * move.temps + move.theta_zero);
     } else if (!move.circular_mode){
         move.acceleration = move.forces / move.weight;
     }
   // move.acceleration = move.forces / move.weight;

}

void DirectionController::update_forces_of_drone(Drone *drone)
{
        auto& move = drone->get_move_data();

        move.forces.x_ = move.dx;
        move.forces.y_ = move.dy;

}

void DirectionController::update_position_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    auto& drone_position = drone->get_position();

    move.temps += 0.1;

    if (move.target_reached){
        // Positioning for circular movement
       // move.theta_zero = 1000;
        drone_position.x_ = move.radius * cos(move.w * move.temps + move.theta_zero);
        drone_position.y_ = move.radius * sin(move.w * move.temps + move.theta_zero);
    } else if (!move.circular_mode) {
        drone_position = drone_position + move.speed;
    }
     //            drone_position = drone_position + move.speed;

    std::cout<<*drone<<std::endl;
}

void DirectionController::update_speed_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    move.speed = 0.9 * (move.speed + move.acceleration);
}
