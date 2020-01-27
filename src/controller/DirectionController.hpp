//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_DIRECTIONCONTROLLER_HPP
#define DRONEPROJECT_DIRECTIONCONTROLLER_HPP


#include "../model/Drone.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"

#define MAX_FORCE 200

class DirectionController: public ServiceProvider
{

public:

    static std::string SERVICE;

    DirectionController();

    void set_drone_target(Drone* drone, const Vector2D& target);

    void prevent_collision_between_drones(Drone* d1, Drone* d2);

    float get_distance_between_drones(Drone* d1, Drone* d2) const;

private:

    void update_acceleration_of_drone(Drone* drone);

    void update_forces_of_drone(Drone* drone);

    void update_position_of_drone(Drone* drone);

    void update_speed_of_drone(Drone* drone);

    std::map<Drone*, TypeUtil::Callback> callbacks_;

};


#endif //DRONEPROJECT_DIRECTIONCONTROLLER_HPP
