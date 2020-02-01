//
// Created by Maanrifa Bacar Ali on 30/01/2020.
//

#ifndef DRONEPROJECT_DRONEZONECHANGEEVENT_HPP
#define DRONEPROJECT_DRONEZONECHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"
#include "../../../model/Server.hpp"
#include "../../../model/MyPolygon.hpp"

class DroneZoneChangeEvent: public Event
{

public:

    DroneZoneChangeEvent(Drone *drone, Server *server, MyPolygon *polygon);

    Drone *get_drone() const;

    Server *get_server() const;

    MyPolygon *get_polygon() const;

    friend std::ostream &operator<<(std::ostream &os, const DroneZoneChangeEvent &event);

private:

    Drone* drone_;

    Server* server_;

    MyPolygon* polygon_;

};


#endif //DRONEPROJECT_DRONEZONECHANGEEVENT_HPP
