//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_DIRECTIONCONTROLLER_HPP
#define DRONEPROJECT_DIRECTIONCONTROLLER_HPP


#include "CollisionController.hpp"
#include "../model/Drone.hpp"

class DirectionController
{

public:

    struct MoveOptions {
        const Position& target = {0, 0};
        const Vector2D& forces = {150000,150000};
        const Vector2D& speed = {};
        const Vector2D& acceleration = {};
        float weight{10};
    };

    DirectionController();

    void move_drone(Drone* drone, MoveOptions move_options);

private:

};


#endif //DRONEPROJECT_DIRECTIONCONTROLLER_HPP
