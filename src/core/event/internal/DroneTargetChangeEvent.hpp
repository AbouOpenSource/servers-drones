//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#ifndef DRONEPROJECT_DRONETARGETCHANGEEVENT_HPP
#define DRONEPROJECT_DRONETARGETCHANGEEVENT_HPP


#include "../Event.hpp"
#include "../../../model/Drone.hpp"
#include "../../../model/Server.hpp"

class DroneTargetChangeEvent: public Event
{

public:

    DroneTargetChangeEvent(Drone *drone, Server *server);

    Drone *get_drone() const;

    Server *get_server() const;

    friend std::ostream &operator<<(std::ostream &os, const DroneTargetChangeEvent &event);

private:

    Drone* drone_;

    Server* server_;

};


#endif //DRONEPROJECT_DRONETARGETCHANGEEVENT_HPP
