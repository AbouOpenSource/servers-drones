//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "Window.hpp"

std::string Window::SERVICE = "WindowService";

Window::Window(int argc, char **argv, InputManager* input_manager)
        : GlutWindow(argc, argv, TITLE, 1000, 800, FIXED),
          ServiceProvider(Window::SERVICE),
          input_manager_(input_manager),
          drawables_(std::vector<Drawable*>())
{}

void Window::onStart()
{
    for (auto & drawable : drawables_) {
        drawable->start(input_manager_);
    }
}

void Window::onDraw()
{
    for (auto & drawable : drawables_) {
        drawable->draw();
    }
}

void Window::onQuit()
{
    for (auto & drawable : drawables_) {
        drawable->quit();
    }
}

void Window::addDrawable(Drawable *drawable)
{
    drawables_.push_back(drawable);
}

void Window::onMouseMove(double cx, double cy)
{
    input_manager_->on_mouse_move(cx, cy);
}

void Window::onMouseDown(int button, double cx, double cy)
{
    input_manager_->on_mouse_down(button, cx, cy);
}

void Window::onKeyPressed(unsigned char c, double cx, double cy)
{
    input_manager_->on_key_pressed(c, cx, cy);
}
