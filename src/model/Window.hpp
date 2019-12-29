#ifndef DRONEPROJECT_WINDOW_HPP
#define DRONEPROJECT_WINDOW_HPP

#include <array>

#include <glutWindow.h>

#include "Mesh.hpp"

class Window: public GlutWindow
{
private:
    std::array<Vector2D, 5> vertices;
    std::array<Triangle*, 3> tris;
    Mesh* mesh;

public:

    /********** Constructor **********/
    Window(const string &title, int argc, char **argv);

    /********** Event **********/
    void onStart() override;

    void onDraw() override;

    void onMouseMove(double cx,double cy) override;

    void onMouseDown(int button,double cx,double cy) override;

    void onKeyPressed(unsigned char c,double x,double y) override;

    void onQuit() override;
};

#endif //DRONEPROJECT_WINDOW_HPP
