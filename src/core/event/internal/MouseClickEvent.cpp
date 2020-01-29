//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "MouseClickEvent.hpp"

MouseClickEvent::MouseClickEvent(Window::MouseClick& mouse_click, const Window::MousePosition &mouse_position)
    : Event(),
    mouse_click_(mouse_click),
    mouse_position_(mouse_position)
{}

Window::MouseClick MouseClickEvent::get_mouse_click() const
{
    return mouse_click_;
}

const Window::MousePosition &MouseClickEvent::get_mouse_position() const
{
    return mouse_position_;
}

ostream &operator<<(std::ostream &os, const MouseClickEvent &event)
{
    os << "Mouse bouton (" << (event.mouse_click_ == 0 ? "LEFT" : "RIGHT")  << ") clicked at position ("
       << event.mouse_position_.X << "," << event.mouse_position_.Y << ")" << std::endl;
    return os;
}
