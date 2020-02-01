//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#include "DeleteDroneEvent.hpp"

DeleteDroneEvent::DeleteDroneEvent(Drone* drone)
        : Event(),
          drone_(drone)
{}

Drone *DeleteDroneEvent::get_drone() const
{
    return drone_;
}

std::ostream &operator<<(std::ostream &os, const DeleteDroneEvent &event)
{
    os << "Deleted drone: " << event.drone_ << std::endl;
    return os;
}

