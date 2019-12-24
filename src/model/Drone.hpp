//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_DRONE_HPP
#define DRONEPROJECT_DRONE_HPP


#include "Position.hpp"
#include "Vector2D.hpp"
#include <math.h>

//why
//#include "Server.hpp"

class Drone {


private:
    Drone(const Vector2D &current_position, const Vector2D &forces, float weight);

    Vector2D current_position_;
    Vector2D speed_;
    Vector2D acceleration_;
    Vector2D forces_;
    float weight_;
    int delta_time = int(3);
    //Server my_server_;

public:

    Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
          Vector2D forces, float weight);

    const Vector2D &getCurrentPosition() const;

    const Vector2D &getSpeed() const;

    const Vector2D &getAcceleration() const;

    const Vector2D &getForces() const;

    void setCurrentPosition(const Vector2D &current_position);

    void setSpeed(const Vector2D &speed);

    void setAcceleration(const Vector2D &acceleration);

    void setForces(const Vector2D &forces);

    void setWeight(float weight);

    void updatePosition();

    void avoidCollisionWith(Drone *ptrDrone);

    float distanceWithOtherDrone(Drone item);
};


#endif //DRONEPROJECT_DRONE_HPP
