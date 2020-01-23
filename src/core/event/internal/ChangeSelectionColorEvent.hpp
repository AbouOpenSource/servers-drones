//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_CHANGESELECTIONCOLOREVENT_HPP
#define DRONEPROJECT_CHANGESELECTIONCOLOREVENT_HPP


#include "../Event.hpp"

class ChangeSelectionColorEvent: public Event
{

public:

    ChangeSelectionColorEvent(int color_id);

private:

    const int color_id_;

};


#endif //DRONEPROJECT_CHANGESELECTIONCOLOREVENT_HPP
