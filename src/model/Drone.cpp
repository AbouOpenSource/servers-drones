//
// Created by abou on 19/12/2019.
//

#include "Drone.hpp"


Drone::Drone(const  Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
             Vector2D forces, float weight) : current_position_(
        current_position), speed_(speed), acceleration_(acceleration), forces_(forces),weight_(weight)
{

}

const Vector2D &Drone::getCurrentPosition() const
{
    return current_position_;
}

const Vector2D &Drone::getSpeed() const
{
    return speed_;
}

const Vector2D &Drone::getAcceleration() const
{
    return acceleration_;
}

void Drone::setCurrentPosition(const Vector2D &current_position)
{
    current_position_ = current_position;
}

void Drone::setSpeed(const Vector2D &speed)
{
    speed_ = speed;
}

void Drone::setAcceleration(const Vector2D &acceleration)
{
    acceleration_ = acceleration;
}


void Drone::setForces(const Vector2D &forces)
{
    forces_ = forces;
}

const Vector2D &Drone::getForces() const
{
    return forces_;
}

void Drone::setWeight(float weight)
{
    Drone::weight_ = weight;
}

Drone::Drone(const Vector2D &current_position, const Vector2D &forces, float weight)
        : current_position_(
        current_position), forces_(forces), weight_(weight), acceleration_(forces/weight), speed_((forces/weight)/delta_time)
{
    /* Drone::setCurrentPosition(current_position);
     Drone::setForces(forces);
     Drone::setWeight(weight);
     Drone::setAcceleration(forces/weight);
     Drone::setSpeed((forces/weight)/3.0);*/
}

void Drone::updatePosition()
{
    current_position_= current_position_+speed_/delta_time;
}



