//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_DRONECONFIGCHANGEEVENT_HPP
#define DRONEPROJECT_DRONECONFIGCHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"

class DroneConfigChangeEvent: public Event
{

public:

    explicit DroneConfigChangeEvent(std::vector<Drone*>& drones);

    std::vector<Drone*> &get_drones() const;

    friend std::ostream &operator<<(std::ostream &os, const DroneConfigChangeEvent &event);

private:

    std::vector<Drone*>& drones_;
};


#endif //DRONEPROJECT_DRONECONFIGCHANGEEVENT_HPP
