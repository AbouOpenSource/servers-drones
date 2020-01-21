//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_WINDOW_HPP
#define DRONEPROJECT_WINDOW_HPP

#define TITLE "Drone Project"

#include <glutWindow.h>
#include "../core/event/input/InputManager.hpp"
#include "../core/ServiceProvider.hpp"
#include "drawable/Drawable.hpp"
#include <vector>
#include <string>

class Window: public GlutWindow, public ServiceProvider
{

public:

    static std::string SERVICE;

    /********** Constructor **********/
    Window(int argc, char **argv, InputManager* input_manager);

    /********** Event **********/
    void onStart() override;

    void onDraw() override;

    void addDrawable(Drawable* drawable);

    void onMouseMove(double cx,double cy) override;

    void onMouseDown(int button,double cx,double cy) override;

    void onKeyPressed(unsigned char c,double x,double y) override;

    void onQuit() override;

private:

    InputManager* input_manager_;

    std::vector<Drawable*> drawables_;

};



#endif //DRONEPROJECT_WINDOW_HPP
