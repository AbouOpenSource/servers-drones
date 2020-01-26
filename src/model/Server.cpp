//
// Created by abou on 19/12/2019.
//

#include <algorithm>
#include "Server.hpp"

Server::Server(std::string &name, std::string& color)
    : name_(name),
      position_({}),
      color_(color),
      selected_(false)
{}

bool Server::is_selected() const
{
    return selected_;
}

void Server::set_selected(bool selected)
{
    selected_ = selected;
}

Vector2D& Server::get_position()
{
    return position_;
}

const string &Server::get_name() const
{
    return name_;
}

const string &Server::get_color() const
{
    return color_;
}

void Server::set_color(const string &color)
{
    color_ = color;
}
