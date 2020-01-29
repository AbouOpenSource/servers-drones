//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "DroneConfigChangeEvent.hpp"

DroneConfigChangeEvent::DroneConfigChangeEvent(std::vector<Drone*> &drones)
    : Event(),
    drones_(drones)
{}

std::vector<Drone *> &DroneConfigChangeEvent::get_drones() const
{
    return drones_;
}

std::ostream &operator<<(std::ostream &os, const DroneConfigChangeEvent &event)
{
    os << "Drone configuration changed" << std::endl;
    return os;
}
