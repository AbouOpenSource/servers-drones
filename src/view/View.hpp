//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_VIEW_HPP
#define DRONEPROJECT_VIEW_HPP

#include "../core/event/EventManager.hpp"
#include "glutWindow.h"

const float BLACK[4] = {0.0, 0.0, 0.0, 0.1f};
const float GREY[4] = {0.75f, 0.75f, 0.75f, 0.1f};
const float RED[4] = {1.0f, 0.0, 0.0, 0.1f};
const float ORANGE[4] = {1.0f, 0.27f, 0.0, 0.1f};
const float YELLOW[4] = {1.0f, 1.0f, 0.0, 0.1f};
const float GREEN[4] = {0.0, 1.0f, 0.0, 0.1f};
const float BLUE[4] = {0.0, 0.0, 1.0f, 0.1f};
const float PINK[4] = {0.9569f, 0.7529f, 0.7961f, 0.1f};
const float CYAN[4] = {0.0, 1.0f, 1.0f, 0.1f};

class View
{

public:

    typedef std::function<int(const std::string& path, int& x, int& y)> TextureLoader;

    class DrawHelper {

    public:

        static std::vector<std::string> COLORS;

        explicit DrawHelper();

        void init(TextureLoader* texture_loader);

        const float* get_color(const std::string& color_name);
        const float* red();
        const float* green();
        const float* blue();
        const float* yellow();
        const float* black();
        const float* orange();
        const float* grey();
        const float* pink();
        const float* cyan();

        int load_texture(const std::string& file_name, int& width, int& height);

    private:

        TextureLoader* texture_loader_;
    };

    View();

    virtual void init(DrawHelper *draw_helper, EventManager *event_manager);

    virtual void start();

    virtual void draw(DrawHelper* draw_helper);

    virtual void quit();
};


#endif //DRONEPROJECT_VIEW_HPP
