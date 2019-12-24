//
// Created by abou on 19/12/2019.
//

#include <algorithm>
#include "Server.hpp"
#include "Circle.hpp"


Server::Server(const Vector2D &speed, const Vector2D &current_position, const std::vector<Drone*> &the_drone) : speed_(
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
                Position center = Position(the_drone_.at(i)->getCurrentPosition().getAxisX(),the_drone_.at(i)->getCurrentPosition().getAxisY());
                Circle zone =Circle(center,Server::getRaduisDeCollision());

                for (int j = 0; j < the_drone_.size(); ++j) {
                        if(i!=j){
                            Position otherCenter =Position(the_drone_.at(j)->getCurrentPosition().getAxisX(),the_drone_.at(j)->getCurrentPosition().getAxisY());
                            Circle otherZone =Circle(otherCenter,Server::getRaduisDeCollision());

                            if(zone.touchWithOther(otherZone)){
                                the_drone_.at(i)->avoidCollisionWith(the_drone_.at(j));
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

