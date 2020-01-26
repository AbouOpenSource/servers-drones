//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "DirectionController.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"


std::string DirectionController::SERVICE = "DirectionService";

DirectionController::DirectionController()
    : ServiceProvider(DirectionController::SERVICE),
      drone_data_({})
{
    auto* event_manager = (EventManager *) ServiceContainer::get_instance()->get_service(EventManager::SERVICE);
    EventManager::Subscription subscription = [this] (Event* e, const TypeUtil::Callback& unsubscribe) {
        for(auto & it : drone_data_) {
            if (it.second.callback) {
                it.second.callback();
            }
        }
    };
    event_manager->subscribe(EventType::FRAME_UPDATE, subscription);
}

void DirectionController::set_drone_target(Drone *drone, const Vector2D &target)
{
    ensure_map_contains(drone);

    DroneData& drone_data = drone_data_[drone];
    MoveData* move = &drone_data.data;

    move->target = target;

    Vector2D& drone_position = drone->get_position();

    drone_data_[drone].callback = [this, drone, move, &drone_position] () {
        move->dx = move->target.x_ - drone_position.x_;
        move->dy = move->target.y_ - drone_position.y_;
        move->distance = sqrt(move->dx * move->dx + move->dy * move->dy);

        move->target_reached = abs(move->dx) < 6 && abs(move->dy) > 75;

        if (!move->circular_mode && move->target_reached) {
            move->circular_mode = true;
        }

        update_forces_of_drone(drone);
        update_acceleration_of_drone(drone);
        update_speed_of_drone(drone);
        update_position_of_drone(drone);

        std::cout << "Distance : " << move->distance << std::endl;
    };
}

void DirectionController::prevent_collision_between_drones(Drone *d1, Drone *d2)
{

    auto* move = get_instant_movement_for_drone(d1);
    auto& d1_pos = d1->get_position();
    auto& d2_pos = d2->get_position();
    //TODO define the force to avoid the collison with the drone passing in args
    float distance = get_distance_between_drones(d1, d2);

    Vector2D ba =  Vector2D(d1_pos.x_ - d2_pos.x_, d1_pos.y_ - d2_pos.y_);

    if (distance < 48) {
        Vector2D force_ba = MAX_FORCE * (ba / distance);
        move->forces = force_ba;
        update_forces_of_drone(d1);
        update_acceleration_of_drone(d1);
        update_speed_of_drone(d1);

    } else if (distance < 96) {
        Vector2D force_ba = ((distance - 96) / (48 - 96)) * (MAX_FORCE * (ba / distance));
        move->forces = force_ba;
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
    auto* move = get_instant_movement_for_drone(drone);
    if (move->target_reached) {
        // Acceleration for circular movement
        move->theta_zero = 0;
        move->acceleration.x_ = (-move->radius) * (move->w * move->w) * cos(move->w * move->temps + move->theta_zero);
        move->acceleration.y_ = (-move->radius) * (move->w * move->w) * sin(move->w * move->temps + move->theta_zero);
    } else if (!move->circular_mode){
        move->acceleration = move->forces / move->weight;
    }
}

void DirectionController::update_forces_of_drone(Drone *drone)
{
    auto* move = get_instant_movement_for_drone(drone);
    if (move->distance > 60) {
        move->forces.x_ = move->dx;
        move->forces.y_ = move->dy;
    }
}

void DirectionController::update_position_of_drone(Drone *drone)
{
    auto* move = get_instant_movement_for_drone(drone);
    auto& drone_position = drone->get_position();

    move->temps += 0.1;

    if (move->target_reached){
        // Positioning for circular movement
        move->theta_zero = 1000;
        drone_position.x_ = move->radius * cos(move->w * move->temps + move->theta_zero);
        drone_position.y_ = move->radius * sin(move->w * move->temps + move->theta_zero);
    } else if (!move->circular_mode) {
        drone_position = drone_position + move->speed;
    }
}

void DirectionController::update_speed_of_drone(Drone *drone)
{
    auto* move = get_instant_movement_for_drone(drone);
    move->speed = 0.8 * (move->speed + move->acceleration);
}

DirectionController::MoveData *DirectionController::get_instant_movement_for_drone(Drone* drone)
{
    return &drone_data_[drone].data;
}

void DirectionController::ensure_map_contains(Drone *drone)
{
    auto it = drone_data_.find(drone);
    if (it == drone_data_.end())
    {
        drone_data_[drone] = {MoveData()};
    }
}
