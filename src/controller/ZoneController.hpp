//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#ifndef DRONEPROJECT_ZONECONTROLLER_HPP
#define DRONEPROJECT_ZONECONTROLLER_HPP


#include "Controller.hpp"
#include "../model/Drone.hpp"
#include "../model/Server.hpp"
#include "DiagramController.hpp"

class ZoneController: public Controller
{

public:

    static std::string SERVICE;

    ZoneController();

private:

    void track_drone_zone_change();

    std::vector<Drone*> drones_;

    DiagramController* diagram_controller_;

};


#endif //DRONEPROJECT_ZONECONTROLLER_HPP
