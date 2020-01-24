//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "Window.hpp"
#include "core/service/ServiceContainer.hpp"
#include "util/VectorUtil.hpp"

std::string Window::SERVICE = "WindowService";

Window::Window(int argc, char **argv)
    : GlutWindow(argc, argv, TITLE, 1000, 800, FIXED),
    ServiceProvider(Window::SERVICE),
    input_manager_((InputManager *) ServiceContainer::get_instance()->get_service(InputManager::SERVICE)),
    event_manager_((EventManager *) ServiceContainer::get_instance()->get_service(EventManager::SERVICE)),
    views_(std::vector<View*>())
{
    draw_helper_ = View::DrawHelper();
}

void Window::onStart()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color

    for (auto & view : views_) {
        view->start();
    }
}

void Window::onDraw()
{
    for (auto & view : views_) {
        view->draw(&draw_helper_);
    }
}

void Window::onQuit()
{
    for (auto & view : views_) {
        view->quit();
    }
}

void Window::addView(View* view)
{
    views_.push_back(view);
    view->init(
            input_manager_,
            event_manager_,
            [] (const std::string &file_name, int &x, int &y) {
        return loadTGATexture(TEXTURE_DIR + file_name + ".tga", x, y);
    });
}

void Window::removeView(View *view)
{
    VectorUtil::delete_object(views_, view);
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
