//
// Created by abou on 19/12/2019.
//

#include "Drone.hpp"
#include "Circle.hpp"


Drone::Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
             Vector2D forces, float weight,Color color,std::string name) : current_position_(
        current_position), speed_(speed), acceleration_(acceleration), forces_(forces), weight_(weight),color_(color),name_(name)
{

}

const Vector2D &Drone::get_current_position() const
{
    return current_position_;
}

const Vector2D &Drone::get_speed() const
{
    return speed_;
}

const Vector2D &Drone::get_acceleration() const
{
    return acceleration_;
}

void Drone::set_current_position(const Vector2D &current_position)
{
    current_position_ = current_position;
}

void Drone::set_speed(const Vector2D &speed)
{
    speed_ = speed;
}

void Drone::set_acceleration(const Vector2D &acceleration)
{
    acceleration_ = acceleration;
}


void Drone::set_forces(const Vector2D &forces)
{
    forces_ = forces;
}

const Vector2D &Drone::get_forces() const
{
    return forces_;
}

void Drone::set_weight(float weight)
{
    Drone::weight_ = weight;
}

Drone::Drone(const Vector2D &current_position, const Vector2D &forces, float weight)
        : current_position_(
        current_position), forces_(forces), weight_(weight), acceleration_(forces / weight),
          speed_((forces / weight) / delta_time)
{

}

void Drone::update_position()
{
    current_position_ = current_position_ + speed_ / delta_time;
}

void Drone::avoid_collision_with(Drone *ptrDrone)
{
    //TODO define the force to avoid the collison with the drone passing in args

    int ForceMAX = 10;
    //float dAB = this->distanceWithOtherDrone(*ptrDrone);
    //Computing of the
    Vector2D BA = new Vector2D(
            Drone::current_position_.getAxisX() - ptrDrone->current_position_.getAxisX(),
            Drone::current_position_.getAxisY() - ptrDrone->current_position_.getAxisY()
    );


    float distance = Drone::distance_with_other_drone(*ptrDrone);
    //10 raduis
    if (distance < 10) {
        //First case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()

    } else {
        //Second case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()


    }

}

float Drone::distance_with_other_drone(Drone item)
{
    return
            sqrt(item.current_position_.getAxisX() - Drone::current_position_.getAxisX() *
                                                     item.current_position_.getAxisX() -
                 Drone::current_position_.getAxisX()
                 +
                 item.current_position_.getAxisY() - Drone::current_position_.getAxisY() *
                                                     item.current_position_.getAxisY() -
                 Drone::current_position_.getAxisY()
            );
}


