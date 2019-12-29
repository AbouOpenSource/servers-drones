#include "Window.hpp"

Window::Window(const string &title, int argc, char **argv)
    : GlutWindow(argc, argv, title, 1000, 800, FIXED)
{
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

    float tab_vect[][2] = {{280, 740}, {700, 750}, {500, 700}, {900, 720}, {50, 410}, {340 , 400} , {650 , 390} , {950 , 300} , {400 , 200} , {550 , 190} , {200 , 50} , {800 , 100}};
    int tab_tri[][3] = {{0,  2,   1}, {0, 4, 2}, {1, 6, 3}, {2, 5, 8}, {2, 6, 1}, {2, 8, 6}, {3, 6, 11},
                        {3 , 11 , 7} , {4 , 5 , 2} , {4 , 8 , 5} , {4 , 10 , 8} , {6 , 8 , 9} , {6 , 9 , 11} , {8 , 10 , 9} , {9 , 10 , 11}};

    mesh_ = new Mesh(tab_vect, 12, tab_tri, 15);

    glClearColor(1.0,1.0,1.0,1.0); // background color
}

void Window::onDraw()
{
    // draw the referential
    glPushMatrix();
    glTranslatef(10,10,0);
    glColor3fv(RED);
    glBegin(GL_QUADS);
    glVertex2f(0.0,-2.0);
    glVertex2f(100.0,-2.0);
    glVertex2f(100.0,2.0);
    glVertex2f(0.0,2.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(110.0,0.0);
    glVertex2f(90.0,-10.0);
    glVertex2f(90.0,10.0);
    glEnd();
    glColor3fv(GREEN);
    glBegin(GL_QUADS);
    glVertex2f(-2.0,0.0);
    glVertex2f(2.0,0.0);
    glVertex2f(2.0,100.0);
    glVertex2f(-2.0,100.0);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0,110.0);
    glVertex2f(-10.0,90.0);
    glVertex2f(10.0,90.0);
    glEnd();
    glPopMatrix();

//    for (auto t:tris_) {
//        t->draw();
//    }
//    for (auto t:tris_) {
//        t->drawCircle();
//    }

    mesh_->draw();
}

void Window::onMouseMove(double cx, double cy)
{
    Vector2D vertex((float) cx,(float) cy);
//    for (auto t:tris_)
//        t->onMouseMove(v);

    mesh_->onMouseMove(vertex);
}

void Window::onMouseDown(int button, double cx, double cy)
{
    Vector2D vertex((float) cx, (float) cy);

    mesh_->onMouseDown(vertex);
}

void Window::onKeyPressed(unsigned char c, double x, double y)
{
}

void Window::onQuit()
{
}