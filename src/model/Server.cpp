//
// Created by abou on 19/12/2019.
//

#include <algorithm>
#include "Server.hpp"

Server::Server(const std::string &name, const std::string& color)
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

std::ostream &operator<<(std::ostream &os, const Server &server)
{
    os << "Server: " <<  "selected_: " << server.selected_ << " position_: " << server.position_ << " name_: " << server.name_
       << " color_: " << server.color_ << std::endl;
    return os;
}
