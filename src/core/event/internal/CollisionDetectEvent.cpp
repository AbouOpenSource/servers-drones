//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "CollisionDetectEvent.hpp"

CollisionDetectEvent::CollisionDetectEvent(Drone *d1, Drone *d2)
    : Event(),
    d1_(d1),
    d2_(d2)
{}

Drone *CollisionDetectEvent::get_first_drone() const
{
    return d1_;
}

Drone *CollisionDetectEvent::get_second_drone() const
{
    return d2_;
}

std::ostream &operator<<(std::ostream &os, const CollisionDetectEvent &event)
{
    os << "Collision detected between: D1(" << event.d1_ << ") and D2(" << event.d2_ << ")" << std::endl;
    return os;
}
