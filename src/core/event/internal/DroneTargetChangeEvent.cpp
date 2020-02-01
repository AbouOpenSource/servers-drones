//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#include "DroneTargetChangeEvent.hpp"

DroneTargetChangeEvent::DroneTargetChangeEvent(Drone *drone, Server *server)
        : Event(),
          drone_(drone),
          server_(server)
{}

Drone *DroneTargetChangeEvent::get_drone() const
{
    return drone_;
}

Server *DroneTargetChangeEvent::get_server() const
{
    return server_;
}

std::ostream &operator<<(std::ostream &os, const DroneTargetChangeEvent &event)
{
    os << "Drone (" << event.drone_->get_id() << ") target is now " << event.server_->get_name() << std::endl;
    return os;
}
