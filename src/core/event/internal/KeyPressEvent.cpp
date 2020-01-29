//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#include "KeyPressEvent.hpp"

KeyPressEvent::KeyPressEvent(Window::Key key, const Window::MousePosition &mouse_position)
    : Event(),
    key_(key),
    mouse_position_(mouse_position)
{}

Window::Key KeyPressEvent::get_key() const
{
    return key_;
}

const Window::MousePosition &KeyPressEvent::get_mouse_position() const
{
    return mouse_position_;
}

ostream &operator<<(std::ostream &os, const KeyPressEvent &event)
{
    os << "Key (" << event.key_ << ") pressed at position ("
    << event.mouse_position_.X << "," << event.mouse_position_.Y << ")" << std::endl;
    return os;
}
