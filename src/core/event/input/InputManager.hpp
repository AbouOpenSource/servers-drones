//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_INPUTMANAGER_HPP
#define DRONEPROJECT_INPUTMANAGER_HPP


#include "../../service/ServiceProvider.hpp"
#include <functional>
#include <vector>


class InputManager: public ServiceProvider
{

public:

    static std::string SERVICE;

    enum Key {
        F1 = 49,
        F2 = 50,
        F3 = 51,
        F4 = 52,
        F5 = 53,
        F6 = 54,
        F7 = 55,
        F8 = 56,
        F9 = 57,
        S = 115,
        D = 100,
        DEL = 127,
        ENTER = 13
    };

    enum MouseClick {
        LEFT,
        RIGHT
    };

    struct MousePosition {
        double X;
        double Y;
    };

    typedef std::function<void(const Key key, const MousePosition& mouse_position)> KeyPressListener;
    typedef std::function<void(const MousePosition& position)> MouseMoveListener;
    typedef std::function<void(const MouseClick& click, const MousePosition& position)> MouseClickListener;

    InputManager();

    void register_key_press_listener(const KeyPressListener& key_press_listener);

    void register_mouse_move_listener(const MouseMoveListener& mouse_move_listener);

    void register_mouse_click_listener(const MouseClickListener& mouse_click_listener);

    MousePosition get_current_mouse_position() const;

    void on_mouse_move(double cx, double cy);

    void on_mouse_down(int button, double cx, double cy) const;

    void on_key_pressed(unsigned char c, double cx, double cy) const;

private:

    std::vector<KeyPressListener> key_press_listeners_;
    std::vector<MouseMoveListener> mouse_move_listeners_;
    std::vector<MouseClickListener> mouse_click_listeners_;

    MousePosition current_mouse_position_;

};


#endif //DRONEPROJECT_INPUTMANAGER_HPP
