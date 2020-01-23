//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "Window.hpp"
#include "../core/ServiceContainer.hpp"

std::string Window::SERVICE = "WindowService";

Window::Window(int argc, char **argv)
    : GlutWindow(argc, argv, TITLE, 1000, 800, FIXED),
    ServiceProvider(Window::SERVICE),
    input_manager_(static_cast<InputManager *>(ServiceContainer::get_instance()->get_service(InputManager::SERVICE))),
    event_manager_(static_cast<EventManager *>(ServiceContainer::get_instance()->get_service(EventManager::SERVICE))),
    drawables_(std::vector<Drawable*>())
{}

void Window::onStart()
{
    for (auto & drawable : drawables_) {
        drawable->start();
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

void Window::addDrawable(Drawable* drawable)
{
    drawables_.push_back(drawable);
    drawable->init(
            input_manager_,
            event_manager_,
            [] (const std::string &file_name, int &x, int &y) {
        return loadTGATexture(TEXTURE_DIR + file_name + ".tga", x, y);
    });

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
