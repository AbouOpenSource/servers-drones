//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "MouseMoveEvent.hpp"

MouseMoveEvent::MouseMoveEvent(Window::MousePosition &mouse_position)
    : Event(),
    mouse_position_(mouse_position)
{}

Window::MousePosition &MouseMoveEvent::get_mouse_position() const
{
    return mouse_position_;
}

ostream &operator<<(std::ostream &os, const MouseMoveEvent &event)
{
    os << "Mouse moved to position (" << event.mouse_position_ << "," << event.mouse_position_.Y << ")" << std::endl;
    return os;
}
