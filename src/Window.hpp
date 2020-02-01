//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_WINDOW_HPP
#define DRONEPROJECT_WINDOW_HPP

#define TITLE "Drone Project"
#define TEXTURE_DIR "../data/assets/texture/"

#include <glutWindow.h>
#include "core/event/EventManager.hpp"
#include "core/service/ServiceProvider.hpp"
#include "view/View.hpp"
#include <vector>
#include <string>

class Window: public GlutWindow, public ServiceProvider
{

public:

    enum Key {
        F1 = 49,
        F2 = 50,
        F3 = 51,
        F4 = 52,
        F5 = 53,
        F6 = 54,
        F7 = 55,
        F8 = 56,
        F9 = 57,
        F10 = 48,
        S = 115,
        D = 100,
        DEL = 127,
        ENTER = 13
    };

    enum MouseClick {
        LEFT,
        RIGHT
    };

    struct MousePosition {
        int X;
        int Y;
    };

    static std::string SERVICE;

    /********** Constructor **********/

    Window(int argc, char **argv);

    /********** Getter **********/

    MousePosition getCurrentMousePosition() const;

    View::DrawHelper* getDrawHelper();

    /********** Event **********/

    void onStart() override;

    void onDraw() override;

    void addView(View* view, bool front = false);

    void removeView(View* view);

    void onMouseMove(double cx,double cy) override;

    void onMouseDown(int button,double cx,double cy) override;

    void onKeyPressed(unsigned char c,double x,double y) override;

    void onQuit() override;

private:

    void publishInputEvent(const char* event_type, Event* event);

    EventManager* event_manager_;

    MousePosition current_mouse_position_;

    View::DrawHelper draw_helper_;

    std::vector<View*> views_;

};



#endif //DRONEPROJECT_WINDOW_HPP
