//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_MOUSECLICKEVENT_HPP
#define DRONEPROJECT_MOUSECLICKEVENT_HPP


#include <ostream>
#include "../Event.hpp"

#include "../../../Window.hpp"

class MouseClickEvent: public Event
{
public:

    MouseClickEvent(Window::MouseClick& mouse_click, const Window::MousePosition &mouse_position);

    Window::MouseClick get_mouse_click() const;

    const Window::MousePosition &get_mouse_position() const;

    friend std::ostream &operator<<(std::ostream &os, const MouseClickEvent &event);

private:

    Window::MouseClick mouse_click_;

    Window::MousePosition mouse_position_;
};


#endif //DRONEPROJECT_MOUSECLICKEVENT_HPP
