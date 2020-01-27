//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_COLLISIONCONTROLLER_HPP
#define DRONEPROJECT_COLLISIONCONTROLLER_HPP


#include <vector>
#include "../model/Drone.hpp"
#include "../model/Circle.hpp"
#include "../Window.hpp"
#include "DirectionController.hpp"
#include "ServerController.hpp"

#define COLLISION_RADIUS 48

class CollisionController: public ServiceProvider
{

public:

    static std::string SERVICE;

    CollisionController();

    void prevent_collision_for_drone(Drone* drone);

    void monitor_trajectory_of_drone(Drone* drone);

    vector<Drone*> & get_drones();

private:

    Circle get_zone_for_drone(Drone * drone);

    DirectionController* direction_controller_;

    ServerController* server_controller_;

    Window* window_;

};


#endif //DRONEPROJECT_COLLISIONCONTROLLER_HPP
