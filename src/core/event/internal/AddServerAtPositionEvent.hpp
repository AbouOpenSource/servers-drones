//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_ADDSERVERATPOSITIONEVENT_HPP
#define DRONEPROJECT_ADDSERVERATPOSITIONEVENT_HPP


#include "../Event.hpp"
#include "../input/InputManager.hpp"

class AddServerAtPositionEvent: public Event
{

public:

    explicit AddServerAtPositionEvent(InputManager::MousePosition position);

private:

    InputManager::MousePosition position_;

};


#endif //DRONEPROJECT_ADDSERVERATPOSITIONEVENT_HPP
