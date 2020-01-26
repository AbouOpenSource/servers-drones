//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_FRAMEUPDATEEVENT_HPP
#define DRONEPROJECT_FRAMEUPDATEEVENT_HPP


#include "../Event.hpp"
#include "../../../Window.hpp"

class FrameUpdateEvent: public Event
{

public:

    FrameUpdateEvent(Window* window);

private:

    Window* window;

};


#endif //DRONEPROJECT_FRAMEUPDATEEVENT_HPP
