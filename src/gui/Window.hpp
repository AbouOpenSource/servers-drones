#ifndef DRONEPROJECT_WINDOW_HPP
#define DRONEPROJECT_WINDOW_HPP

#include <array>

#include <glutWindow.h>

#include "../model/Mesh.hpp"

class Window: public GlutWindow
{
private:
    std::array<Vector2D, 5> vertices_;
    std::array<Triangle*, 3> tris_;
    std::vector<Server> servers_;
    Mesh* mesh_;

public:

    /********** Constructor **********/
    Window(const string &title, int argc, char **argv, std::vector<Server>& servers);

    /********** Event **********/
    void onStart() override;

    void onDraw() override;

    void onMouseMove(double cx,double cy) override;

    void onMouseDown(int button,double cx,double cy) override;

    void onKeyPressed(unsigned char c,double x,double y) override;

    void onQuit() override;
};

#endif //DRONEPROJECT_WINDOW_HPP
