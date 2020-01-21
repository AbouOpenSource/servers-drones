//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include <iostream>
#include "InputManager.hpp"

std::string InputManager::SERVICE = "InputService";

InputManager::InputManager()
        : ServiceProvider(InputManager::SERVICE),
          current_mouse_position_({0, 0}),
          key_press_listeners_(std::vector<KeyPressListener>()),
          mouse_move_listeners_(std::vector<MouseMoveListener>()),
          mouse_click_listeners_(std::vector<MouseClickListener>())
{}

void InputManager::register_key_press_listener(const InputManager::KeyPressListener& key_press_listener)
{
    key_press_listeners_.push_back(key_press_listener);
}

void InputManager::register_mouse_move_listener(const InputManager::MouseMoveListener& mouse_move_listener)
{
    mouse_move_listeners_.push_back(mouse_move_listener);
}

void InputManager::register_mouse_click_listener(const InputManager::MouseClickListener& mouse_click_listener)
{
    mouse_click_listeners_.push_back(mouse_click_listener);
}

InputManager::MousePosition InputManager::get_current_mouse_position() const
{
    return current_mouse_position_;
}

void InputManager::on_mouse_move(double cx, double cy)
{
    current_mouse_position_.X = cx;
    current_mouse_position_.Y = cy;

    MousePosition mouse_position = {cx, cy};

    for (auto & mouse_move_listener : mouse_move_listeners_) {
        mouse_move_listener(mouse_position);
    }
}

void InputManager::on_mouse_down(int button, double cx, double cy) const
{
    MousePosition mouse_position = {cx, cy};
    MouseClick mouse_click = button == 0 ? LEFT : RIGHT;

    for (auto & mouse_click_listener : mouse_click_listeners_) {
        mouse_click_listener(mouse_click, mouse_position);
    }
}

void InputManager::on_key_pressed(unsigned char c, double cx, double cy) const
{
    MousePosition mouse_position = {cx, cy};

    for (auto & key_press_listener : key_press_listeners_) {
        key_press_listener(static_cast<Key>(c), mouse_position);
    }
}

