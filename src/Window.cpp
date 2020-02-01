//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "Window.hpp"
#include "core/service/ServiceContainer.hpp"
#include "util/VectorUtil.hpp"
#include "core/event/internal/EventType.hpp"
#include "core/event/internal/FrameUpdateEvent.hpp"
#include "core/event/internal/MouseMoveEvent.hpp"
#include "core/event/internal/KeyPressEvent.hpp"
#include "core/event/internal/MouseClickEvent.hpp"

std::string Window::SERVICE = "WindowService";

Window::Window(int argc, char **argv)
    : GlutWindow(argc, argv, TITLE, 1000, 800, FIXED),
    ServiceProvider(Window::SERVICE),
    views_({}),
    current_mouse_position_({0, 0}),
    event_manager_((EventManager *) ServiceContainer::get_instance()->get_service(EventManager::SERVICE)),
    draw_helper_()
{
    draw_helper_.init(new View::TextureLoader ([](const std::string &file_name, int &x, int &y) {
        return loadTGATexture(TEXTURE_DIR + file_name + ".tga", x, y);
    }), new View::TextWriter([](const std::string &text, int x, int y, View::WriteOptions opts) {
        drawText(x, y, text, opts.align, opts.font);
    }));
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
    FrameUpdateEvent event(this);
    event_manager_->publish(EventType::FRAME_UPDATED, &event);
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

void Window::addView(View* view, bool front)
{
    if (front) {
        views_.insert(views_.begin(), view);
    } else {
        views_.push_back(view);
    }
    view->init(&draw_helper_, ServiceContainer::get_instance());
}

void Window::removeView(View *view)
{
    VectorUtil::delete_object(views_, view);
}

void Window::onMouseMove(double cx, double cy)
{
    current_mouse_position_.X = (int)cx;
    current_mouse_position_.Y = (int)cy;

    MousePosition mouse_position{(int)cx, (int)cy};
    publishInputEvent(EventType::MOUSE_MOVED, new MouseMoveEvent(mouse_position));
}

void Window::onMouseDown(int button, double cx, double cy)
{
    MousePosition mouse_position{(int)cx, (int)cy};
    MouseClick mouse_click = button == 0 ? LEFT : RIGHT;

    publishInputEvent(EventType::MOUSE_CLICKED, new MouseClickEvent(mouse_click, mouse_position));
}

void Window::onKeyPressed(unsigned char c, double cx, double cy)
{
    MousePosition mouse_position{(int)cx, (int)cy};

    publishInputEvent(EventType::KEY_PRESSED, new KeyPressEvent(static_cast<Key>(c), mouse_position));
}

void Window::publishInputEvent(const char *event_type, Event* event)
{
    event_manager_->publish(event_type, event);
    event_manager_->publish(EventType::INPUT, event);
}

Window::MousePosition Window::getCurrentMousePosition() const
{
    return current_mouse_position_;
}

View::DrawHelper* Window::getDrawHelper()
{
    return &draw_helper_;
}
