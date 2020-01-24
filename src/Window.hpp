//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_WINDOW_HPP
#define DRONEPROJECT_WINDOW_HPP

#define TITLE "Drone Project"
#define TEXTURE_DIR "../data/assets/texture/"

#include <glutWindow.h>
#include "core/event/input/InputManager.hpp"
#include "core/event/EventManager.hpp"
#include "core/service/ServiceProvider.hpp"
#include "view/View.hpp"
#include <vector>
#include <string>

class Window: public GlutWindow, public ServiceProvider
{

public:

    static std::string SERVICE;

    /********** Constructor **********/
    Window(int argc, char **argv);

    /********** Event **********/

    void onStart() override;

    void onDraw() override;

    void addView(View* view);

    void removeView(View* view);

    void onMouseMove(double cx,double cy) override;

    void onMouseDown(int button,double cx,double cy) override;

    void onKeyPressed(unsigned char c,double x,double y) override;

    void onQuit() override;

private:

    InputManager* input_manager_;

    EventManager* event_manager_;

    View::DrawHelper draw_helper_;

    std::vector<View*> views_;

};



#endif //DRONEPROJECT_WINDOW_HPP
