//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_MOUSEMOVEEVENT_HPP
#define DRONEPROJECT_MOUSEMOVEEVENT_HPP


#include <ostream>
#include "../../../Window.hpp"
#include "../Event.hpp"

class MouseMoveEvent: public Event
{

public:

    MouseMoveEvent(Window::MousePosition &mouse_position);

    Window::MousePosition &get_mouse_position() const;

    friend std::ostream &operator<<(std::ostream &os, const MouseMoveEvent &event);

private:

    Window::MousePosition& mouse_position_;

};


#endif //DRONEPROJECT_MOUSEMOVEEVENT_HPP
