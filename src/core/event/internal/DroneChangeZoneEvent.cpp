//
// Created by Maanrifa Bacar Ali on 30/01/2020.
//

#include "DroneChangeZoneEvent.hpp"

DroneChangeZoneEvent::DroneChangeZoneEvent(Drone *drone, Server *server, Polygon *polygon)
    : Event(),
    drone_(drone),
    server_(server),
    polygon_(polygon)
{}

Drone *DroneChangeZoneEvent::get_drone() const
{
    return drone_;
}

Server *DroneChangeZoneEvent::get_server() const
{
    return server_;
}

Polygon *DroneChangeZoneEvent::get_polygon() const
{
    return polygon_;
}

std::ostream &operator<<(std::ostream &os, const DroneChangeZoneEvent &event)
{
    os << "Drone (" << event.drone_->get_id() << ") is now in " << event.server_->get_name() << " zone" << std::endl;
    return os;
}
