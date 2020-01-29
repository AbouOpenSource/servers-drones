//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_FRAMEUPDATEEVENT_HPP
#define DRONEPROJECT_FRAMEUPDATEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../Window.hpp"

class FrameUpdateEvent: public Event
{

public:

    FrameUpdateEvent(Window* window);

    friend std::ostream &operator<<(std::ostream &os, const FrameUpdateEvent &event);

private:

    Window* window_;

};


#endif //DRONEPROJECT_FRAMEUPDATEEVENT_HPP
