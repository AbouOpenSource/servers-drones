//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "AddDroneEvent.hpp"

AddDroneEvent::AddDroneEvent(Drone* drone)
    : Event(),
    drone_(drone)
{}

Drone *AddDroneEvent::get_drone() const
{
    return drone_;
}

std::ostream &operator<<(std::ostream &os, const AddDroneEvent &event)
{
    os << "Added drone: " << event.drone_ << std::endl;
    return os;
}
