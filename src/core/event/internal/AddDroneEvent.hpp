//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_ADDDRONEEVENT_HPP
#define DRONEPROJECT_ADDDRONEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"


class AddDroneEvent: public Event
{

public:

    explicit AddDroneEvent(Drone* drone);

    Drone *get_drone() const;

    friend std::ostream &operator<<(std::ostream &os, const AddDroneEvent &event);

private:

    Drone* drone_;

};


#endif //DRONEPROJECT_ADDDRONEEVENT_HPP
