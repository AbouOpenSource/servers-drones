//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_COLLISIONDETECTEVENT_HPP
#define DRONEPROJECT_COLLISIONDETECTEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Drone.hpp"

class CollisionDetectEvent: public Event
{

public:

    CollisionDetectEvent(Drone* d1, Drone* d2);

    Drone *get_first_drone() const;

    Drone *get_second_drone() const;

    friend std::ostream &operator<<(std::ostream &os, const CollisionDetectEvent &event);

private:

    Drone* d1_;
    Drone* d2_;

};


#endif //DRONEPROJECT_COLLISIONDETECTEVENT_HPP
