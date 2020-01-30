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
#include "Controller.hpp"
#include "../../data/config/config.hpp"

class
CollisionController: public Controller
{

public:

    static std::string SERVICE;

    CollisionController();

    void prevent_collision_for_drone(Drone* drone);

private:

    Circle get_zone_for_drone(Drone * drone);

    std::vector<Drone*> drones_;

};


#endif //DRONEPROJECT_COLLISIONCONTROLLER_HPP
