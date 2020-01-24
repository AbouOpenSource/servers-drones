//
// Created by abou on 19/12/2019.
//

#include <algorithm>
#include "Server.hpp"
#include "Circle.hpp"

Server::Server(std::string &name, std::string& color)
    : name_(name),
    current_position_({}),
    color_(color),
    collision_radius_(15),
    expected_drone_count_(0),
    d_max_(0),
    selected_(false)
{}

const Vector2D &Server::get_position() const
{
    return current_position_;
}

void Server::set_current_position(const Vector2D &current_position)
{
    current_position_ = current_position;
}

float Server::get_collision_radius() const
{
    return collision_radius_;
}

int Server::get_expected_drone_count()
{
    return expected_drone_count_;
}

void Server::set_collision_radius(float collision_radius)
{
    collision_radius_ = collision_radius;
}

float Server::get_d_max() const
{
    return d_max_;
}

void Server::set_expected_drone_count(int expected_drone_count)
{
    expected_drone_count_ = expected_drone_count;
}

void Server::set_d_max(float d_max)
{
    d_max_ = d_max;
}

const std::string &Server::get_name() const
{
    return name_;
}

const std::string &Server::get_color() const
{
    return color_;
}

void Server::set_color(const std::string &color)
{
    color_ = color;
}

bool Server::is_selected() const
{
    return selected_;
}

void Server::set_selected(bool selected)
{
    Server::selected_ = selected;
}