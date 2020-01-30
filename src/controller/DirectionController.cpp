//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "DirectionController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/CollisionDetectEvent.hpp"
#include "../core/event/internal/DroneChangeZoneEvent.hpp"


std::string DirectionController::SERVICE = "DirectionService";

DirectionController::DirectionController()
    : Controller(DirectionController::SERVICE),
      callbacks_({})
{
    event_manager_->subscribe(EventType::FRAME_UPDATED, [this] (Event* e, const EventManager::EventDetail& detail) {
        for (auto & it : callbacks_) {
            it.second();
        }
    });

    event_manager_->subscribe(EventType::DRONE_CHANGED_ZONE, [this] (Event* e, const EventManager::EventDetail& detail) {
        auto* event = ((DroneChangeZoneEvent*)e);
        set_drone_target(event->get_drone(), event->get_server()->get_position());
    });

    event_manager_->subscribe(EventType::COLLISION_DETECTED, [this] (Event* e, const EventManager::EventDetail& detail) {
        auto* collision = (CollisionDetectEvent*)e;
        prevent_collision_between_drones(collision->get_first_drone(), collision->get_second_drone());
    });
}

void DirectionController::set_drone_target(Drone *drone, const Vector2D &target)
{
    auto& move = drone->get_move_data();

    move.target = target;

    Vector2D& drone_position = drone->get_position();

    callbacks_[drone] = [this, drone, &move, &drone_position] () {
        if(!move.target_reached){

            move.dx = (move.target.x_ - drone_position.x_);
            move.dy = (move.target.y_ - drone_position.y_);
            move.distance = sqrt(move.dx * move.dx + move.dy * move.dy);
            move.dx /= move.distance;
            move.dy /= move.distance;
            move.dx *= 20;
            move.dy *= 20;
        } else {
            move.dx = (move.target.x_ - drone_position.x_);
            move.dy = (move.target.y_ - drone_position.y_);
            move.distance = sqrt(move.dx * move.dx + move.dy * move.dy);
            move.dx /= move.distance;
            move.dy /= move.distance;
            move.dx *= 0;
            move.dy *= 0;
        }

        move.target_reached = move.distance < TARGET_REACHED_MAX_DISTANCE;

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


    //TODO define the force to avoid the collison with the drone passing in args
    float distance = get_distance_between_drones(d1, d2);

    Vector2D ba =  Vector2D(d1_pos.x_ - d2_pos.x_, d1_pos.y_ - d2_pos.y_);
    //   Vector2D ba =  Vector2D(d2_pos.x_ - d1_pos.x_, d2_pos.y_ - d1_pos.y_);

    if (distance < COLLISION_MIN) {
        Vector2D force_ba = MAX_FORCE * (ba / distance);
        move.forces = force_ba;
        //move.dx=force_ba.x_;
        //move.dy=force_ba.y_;

    } else if (distance < COLLISION_MAX) {
        //std::cout<<"Second condition"<<std::endl;
        Vector2D force_ba = ((distance - COLLISION_MAX) / (COLLISION_MIN - COLLISION_MAX)) * (MAX_FORCE * (ba / distance));

        move.forces = force_ba;

        move.dx = force_ba.x_;
        move.dy = force_ba.y_;
    }
    update_forces_of_drone(d1);
    update_acceleration_of_drone(d1);
    update_speed_of_drone(d1);
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

void DirectionController::update_forces_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    move.forces.x_ = move.dx;
    move.forces.y_ = move.dy;
}

void DirectionController::update_acceleration_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    if (move.circular_mode) {
        // Acceleration for circular movement
        move.theta_zero = CIRCULAR_ACCELERATION_THETA_ZERO;
        move.radius = CIRCULAR_ACCELERATION_RADIUS;
        move.acceleration.x_ = (-move.radius) * (move.w * move.w) * cos(move.w * move.temps + move.theta_zero);
        move.acceleration.y_ = (-move.radius) * (move.w * move.w) * sin(move.w * move.temps + move.theta_zero);
    } else {
        move.acceleration = move.forces / move.weight;
    }
    /*     if (move.target_reached) {
         // Acceleration for circular movement
         move.theta_zero = 0;
         move.radius = 100;
         move.acceleration.x_ = (-move.radius) * (move.w * move.w) * cos(move.w * move.temps + move.theta_zero);
         move.acceleration.y_ = (-move.radius) * (move.w * move.w) * sin(move.w * move.temps + move.theta_zero);
     } else if (!move.circular_mode){
         move.acceleration = move.forces / move.weight;
     }*/
    // move.acceleration = move.forces / move.weight;

}

void DirectionController::update_position_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    auto& drone_position = drone->get_position();

    move.temps += DELTA_TIME;

    if (move.circular_mode){
        // Positioning for circular movement
        move.theta_zero = CIRCULAR_POSITION_THETA_ZERO;
        drone_position.x_ = move.radius * cos(move.w * move.temps + move.theta_zero);
        drone_position.y_ = move.radius * sin(move.w * move.temps + move.theta_zero);
    } else {
        drone_position = drone_position + move.speed;
    }/*
    if (move.target_reached){
        // Positioning for circular movement
       // move.theta_zero = 1000;
        drone_position.x_ = move.radius * cos(move.w * move.temps + move.theta_zero);
        drone_position.y_ = move.radius * sin(move.w * move.temps + move.theta_zero);
    } else if (!move.circular_mode) {
        drone_position = drone_position + move.speed;
    }*/
    //    drone_position = drone_position + move.speed;
}

void DirectionController::update_speed_of_drone(Drone *drone)
{
    auto& move = drone->get_move_data();
    move.speed = SPEED_COEFFICIENT * (move.speed + move.acceleration);
}
