//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#ifndef DRONEPROJECT_DELETEDRONEEVENT_HPP
#define DRONEPROJECT_DELETEDRONEEVENT_HPP


#include "../Event.hpp"
#include "../../../model/Drone.hpp"

class DeleteDroneEvent: public Event
{

public:

    explicit DeleteDroneEvent(Drone* drone);

    Drone *get_drone() const;

    friend std::ostream &operator<<(std::ostream &os, const DeleteDroneEvent &event);

private:

    Drone* drone_;

};


#endif //DRONEPROJECT_DELETEDRONEEVENT_HPP
