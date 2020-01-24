//
// Created by abou on 19/12/2019.
//

#include "Drone.hpp"
#include "Circle.hpp"

Drone::Drone(const int id)
    : id_(id),
    weight_(0),
    delta_time_(1)
{}

void Drone::init(const Vector2D &current_position, const Vector2D &forces, float weight, const Vector2D &speed,
                 const Vector2D &acceleration)
{
    current_position_ = current_position;
    speed_ = speed;
    acceleration_ = acceleration;
    forces_ = forces;
    weight_ = weight;
}

int Drone::get_id() const
{
    return id_;
}

const string &Drone::get_server_name() const
{
    return server_name_;
}

void Drone::set_server_name(const string &server_name)
{
    server_name_ = server_name;
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

void Drone::update_position()
{
    current_position_ = current_position_ + speed_ / delta_time_;
}

void Drone::avoid_collision_with(Drone* drone)
{
    //TODO define the force to avoid the collison with the drone passing in args

    int ForceMAX = 10;
    //float dAB = this->distanceWithOtherDrone(*ptrDrone);
    //Computing of the
    Vector2D *BA = new Vector2D(
            Drone::current_position_.x_ - drone->current_position_.x_,
            Drone::current_position_.y_ - drone->current_position_.y_
    );


    float distance = Drone::distance_from(drone);
    //10 raduis
    if (distance < 10) {
        //First case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()

    } else {
        //Second case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()


    }

}

float Drone::distance_from(Drone *item)
{
    return sqrt(
            item->current_position_.x_
            - Drone::current_position_.x_
            * item->current_position_.x_
            - Drone::current_position_.x_
            + item->current_position_.y_
            - Drone::current_position_.y_
            * item->current_position_.y_
            - Drone::current_position_.y_
    );
}

std::ostream &operator<<(std::ostream &os, const Drone &dt)
{
    os << "Drone(" << dt.id_ << ") :" << dt.get_current_position().x_ << '/' << dt.get_current_position().y_ << '/';
    return os;
}

void Drone::add_target(Vector2D item)
{

}


