//
// Created by Maanrifa Bacar Ali on 30/01/2020.
//

#include "DroneZoneChangeEvent.hpp"

DroneZoneChangeEvent::DroneZoneChangeEvent(Drone *drone, Server *server, MyPolygon *polygon)
    : Event(),
    drone_(drone),
    server_(server),
    polygon_(polygon)
{}

Drone *DroneZoneChangeEvent::get_drone() const
{
    return drone_;
}

Server *DroneZoneChangeEvent::get_server() const
{
    return server_;
}

MyPolygon *DroneZoneChangeEvent::get_polygon() const
{
    return polygon_;
}

std::ostream &operator<<(std::ostream &os, const DroneZoneChangeEvent &event)
{
    os << "Drone (" << event.drone_->get_id() << ") is now in " << event.server_->get_name() << " zone" << std::endl;
    return os;
}
