//
// Created by Maanrifa Bacar Ali on 30/01/2020.
//

#ifndef DRONEPROJECT_DRONEZONECHANGEEVENT_HPP
#define DRONEPROJECT_DRONEZONECHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"
#include "../../../model/Server.hpp"
#include "../../../model/Polygon.hpp"

class DroneZoneChangeEvent: public Event
{

public:

    DroneZoneChangeEvent(Drone *drone, Server *server, Polygon *polygon);

    Drone *get_drone() const;

    Server *get_server() const;

    Polygon *get_polygon() const;

    friend std::ostream &operator<<(std::ostream &os, const DroneZoneChangeEvent &event);

private:

    Drone* drone_;

    Server* server_;

    Polygon* polygon_;

};


#endif //DRONEPROJECT_DRONEZONECHANGEEVENT_HPP
