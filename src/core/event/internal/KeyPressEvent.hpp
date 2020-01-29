//
// Created by Maanrifa Bacar Ali on 28/01/2020.
//

#ifndef DRONEPROJECT_KEYPRESSEVENT_HPP
#define DRONEPROJECT_KEYPRESSEVENT_HPP


#include <ostream>
#include "../Event.hpp"

#include "../../../Window.hpp"

class KeyPressEvent: public Event
{

public:

    KeyPressEvent(Window::Key key, const Window::MousePosition &mouse_position);

    Window::Key get_key() const;

    const Window::MousePosition &get_mouse_position() const;

    friend std::ostream &operator<<(std::ostream &os, const KeyPressEvent &event);

private:

    Window::Key key_;

    Window::MousePosition mouse_position_;

};


#endif //DRONEPROJECT_KEYPRESSEVENT_HPP
