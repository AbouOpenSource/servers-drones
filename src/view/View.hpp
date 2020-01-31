//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_VIEW_HPP
#define DRONEPROJECT_VIEW_HPP

#include "../core/event/EventManager.hpp"
#include "../../data/config/config.hpp"
#include "glutWindow.h"

const float WHITE[4] = {1.0, 1.0, 1.0, 0.15f};
const float BLACK[4] = {0.0, 0.0, 0.0, 1.0f};
const float GREY[4] = {0.75f, 0.75f, 0.75f, 1.0f};
const float RED[4] = {1.0f, 0.0, 0.0, 1.0f};
const float ORANGE[4] = {1.0f, 0.27f, 0.0, 1.0f};
const float YELLOW[4] = {1.0f, 1.0f, 0.0, 1.0f};
const float GREEN[4] = {0.0, 1.0f, 0.0, 1.0f};
const float BLUE[4] = {0.0, 0.0, 1.0f, 1.0f};
const float PINK[4] = {0.9569f, 0.7529f, 0.7961f, 1.0f};
const float CYAN[4] = {0.0, 1.0f, 1.0f, 1.0f};

class View
{

public:

    struct WriteOptions {
        GlutWindow::textAlign align;
        void* font;
    };

    typedef std::function<int(const std::string& path, int& x, int& y)> TextureLoader;
    typedef std::function<void(const std::string& path, int x, int y, WriteOptions opts)> TextWriter;

    class DrawHelper {

    public:

        static std::vector<std::string> COLORS;

        explicit DrawHelper();

        ~DrawHelper();

        void init(TextureLoader* texture_loader, TextWriter * text_writer);

        const float* parse(const std::string& color_name);
        const float* red();
        const float* green();
        const float* blue();
        const float* yellow();
        const float* black();
        const float* orange();
        const float* grey();
        const float* pink();
        const float* cyan();
        const float* white();
        const float* dynamic_color();

        const std::string dynamic_color_string();

        int load_texture(const std::string& file_name, int& width, int& height);

        void write_text(const std::string& text, int x, int y,
                WriteOptions opts = {GlutWindow::ALIGN_LEFT, GLUT_BITMAP_8_BY_13});

    private:

        const float* parse_dynamic_color(const std::string& color);

        const float* push_dynamic_color(const string &color, float d, float d1, float d2);

        float random_float();

        TextureLoader* texture_loader_;

        TextWriter* text_writer_;

        std::map<std::string, float*> colors_;
    };

    View();

    virtual void init(DrawHelper *draw_helper, EventManager *event_manager);

    virtual void start();

    virtual void draw(DrawHelper* draw_helper);

    virtual void quit();
};


#endif //DRONEPROJECT_VIEW_HPP
