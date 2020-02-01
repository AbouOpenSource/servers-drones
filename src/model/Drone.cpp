//
// Created by abou on 19/12/2019.
//

#include "Drone.hpp"
#include "Circle.hpp"

Drone::Drone(const int id): id_(id), move_data_({})
{}

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

const std::string &Drone::get_target_server_name() const
{
    return target_server_name_;
}

void Drone::set_target_server_name(const std::string &server_name)
{
    target_server_name_ = server_name;
}

Vector2D& Drone::get_position()
{
    return position_;
}

Drone::MoveData &Drone::get_move_data()
{
    return move_data_;
}

std::ostream &operator<<(std::ostream &os, const Drone &dt)
{
    os << "Drone(" << dt.id_ << ") :" << dt.position_.x_ << '/' << dt.position_.y_ << '/';
    return os;
}


