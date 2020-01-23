//
// Created by abou on 19/12/2019.
//

#include <algorithm>
#include "Server.hpp"
#include "Circle.hpp"

Server::Server(std::string& name, Vector2D &current_position, std::string color)
    : name_(name),
    current_position_(current_position),
    color_(color),
    raduisDeCollision(0),
    desiredNumberOfDrones(0),
    dMax(0)
{
}

//Server::Server(std::string& name, Vector2D &current_position, Color color)
//        : name_(name),
//          current_position_(current_position),
//          color_(color),
//          raduisDeCollision(0),
//          desiredNumberOfDrones(0),
//          dMax(0)
//{
//}

Server::Server(
        const Vector2D &speed,
        const Vector2D &current_position,
        const std::vector<Drone*> &the_drone
        ) : speed_(
        speed), current_position_(current_position), the_drone_(the_drone), raduisDeCollision(15)
{}

const Vector2D &Server::getSpeed() const
{
    return speed_;
}

const Vector2D &Server::getCurrentPosition() const
{
    return current_position_;
}

const std::vector<Drone*> &Server::getTheDrone() const
{
    return the_drone_;
}

void Server::setSpeed(const Vector2D &speed)
{
    speed_ = speed;
}

void Server::setCurrentPosition(const Vector2D &current_position)
{
    current_position_ = current_position;
}

void Server::setTheDrone(const std::vector<Drone*> &the_drone)
{
    the_drone_ = the_drone;
}

void Server::detectCollision()
{

    //TODO i want some this thing like constant for the size of windows
        if(!the_drone_.empty()){

            for(int i = 0; the_drone_.size() > i; i++){
                //TODO make more test to check if i get the right values
               //I create here the circle circoncrit of my drone for test if the collision event can occurs
                Position center = Position(the_drone_.at(i)->get_current_position().x_,
                                           the_drone_.at(i)->get_current_position().y_);
                Circle zone =Circle(center,Server::getRaduisDeCollision());

                for (int j = 0; j < the_drone_.size(); ++j) {
                        if(i!=j){
                            Position otherCenter =Position(the_drone_.at(j)->get_current_position().x_,
                                                           the_drone_.at(j)->get_current_position().y_);
                            Circle otherZone =Circle(otherCenter,Server::getRaduisDeCollision());

                            if(zone.touch_with_other(otherZone)){
                                the_drone_.at(i)->avoid_collision_with(the_drone_.at(j));
                            }
                        }
                }
            }
        }
}

const float Server::getRaduisDeCollision() const
{
    return raduisDeCollision;
}

int Server::getCurrentNumberOfDrones()
{
    return the_drone_.size();
}

int Server::getDesiredNumberOfDrones()
{
    return desiredNumberOfDrones;
}

void Server::connectDrone(Drone *ptrDrone)
{
        the_drone_.push_back(ptrDrone);
}

void Server::disconnectDrone(Drone *ptrDrone)
{
    std::remove(the_drone_.begin(), the_drone_.end(), ptrDrone);
}

void Server::setRaduisDeCollision(float raduis_de_collision)
{
    raduisDeCollision = raduis_de_collision;
}


float Server::getDMax() const
{
    return dMax;
}

void Server::setDesiredNumberOfDrones(int desired_number_of_drones)
{
    desiredNumberOfDrones = desired_number_of_drones;
}

void Server::setDMax(float d_max)
{
    dMax = d_max;
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

//Color color_value_of(std::string color)
//{
//    if (color == "RED") return Color::red;
//    if (color == "GREEN") return Color::green;
//    if (color == "BLUE") return Color::blue;
//    if (color == "PINK") return Color::pink;
//    if (color == "YELLOW") return Color::yellow;
//    if (color == "CYAN") return Color::cyan;
//
//    return Color::red;
//}