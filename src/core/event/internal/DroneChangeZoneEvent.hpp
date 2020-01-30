//
// Created by Maanrifa Bacar Ali on 30/01/2020.
//

#ifndef DRONEPROJECT_DRONECHANGEZONEEVENT_HPP
#define DRONEPROJECT_DRONECHANGEZONEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"
#include "../../../model/Server.hpp"
#include "../../../model/Polygon.hpp"

class DroneChangeZoneEvent: public Event
{

public:

    DroneChangeZoneEvent(Drone *drone, Server *server, Polygon *polygon);

    Drone *get_drone() const;

    Server *get_server() const;

    Polygon *get_polygon() const;

    friend std::ostream &operator<<(std::ostream &os, const DroneChangeZoneEvent &event);

private:

    Drone* drone_;

    Server* server_;

    Polygon* polygon_;

};


#endif //DRONEPROJECT_DRONECHANGEZONEEVENT_HPP
