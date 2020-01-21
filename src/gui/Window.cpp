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

void Window::onStart()
{
    vertices_[0].set(40, 80);
    vertices_[1].set(460, 80);
    vertices_[2].set(240, 360);
    vertices_[3].set(890, 400);
    vertices_[4].set(220, 600);

//    tris_[0] = new triangle(&vertices_[0],&vertices_[1],&vertices_[2]);
//    tris_[1] = new triangle(&vertices_[1],&vertices_[3],&vertices_[2]);
//    tris_[2] = new triangle(&vertices_[2],&vertices_[3],&vertices_[4]);

    // Coordinates
//    float tab_vect[][2] = {{280, 740}, {700, 750}, {500, 700}, {900, 720}, {50, 410}, {340 , 400} , {650 , 390} , {950 , 300} , {400 , 200} , {550 , 190} , {200 , 50} , {800 , 100}};

    //
//    int tab_tri[][3] = {{0,  2,   1}, {0, 4, 2}, {1, 6, 3}, {2, 5, 8}, {2, 6, 1}, {2, 8, 6}, {3, 6, 11},
//                        {3 , 11 , 7} , {4 , 5 , 2} , {4 , 8 , 5} , {4 , 10 , 8} , {6 , 8 , 9} , {6 , 9 , 11} , {8 , 10 , 9} , {9 , 10 , 11}};

//    mesh_ = new Mesh(tab_vect, 12, tab_tri, 15);

    glClearColor(1.0,1.0,1.0,1.0); // background color
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
