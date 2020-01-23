//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_CHANGESERVERCOLOREVENT_HPP
#define DRONEPROJECT_CHANGESERVERCOLOREVENT_HPP


#include "../Event.hpp"

class ChangeServerColorEvent: public Event
{

public:

    ChangeServerColorEvent(int color_id);

private:

    const int color_id_;

};


#endif //DRONEPROJECT_CHANGESERVERCOLOREVENT_HPP
