//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "View.hpp"

View::View()
{}

void View::init(InputManager* input_manager, EventManager* event_manager, const TextureLoader& texture_loader)
{}

void View::start()
{}

void View::draw(DrawHelper* draw_helper)
{}

void View::quit()
{}

View::DrawHelper::DrawHelper()
{}

const float * View::DrawHelper::get_color(const std::string &color_name)
{
	if (color_name == "BLACK") {
        return BLACK;
    }
	if (color_name == "GREY") {
        return GREY;
    }
	if (color_name == "RED") {
        return RED;
    }
	if (color_name == "ORANGE") {
        return ORANGE;
    }
	if (color_name == "YELLOW") {
        return YELLOW;
    }
	if (color_name == "GREEN") {
        return GREEN;
    }
	if (color_name == "BLUE") {
        return BLUE;
    }
	if (color_name == "PINK") {
        return PINK;
    }
	if (color_name == "CYAN") {
        return CYAN;
    }

    return YELLOW;
}

const float *View::DrawHelper::red()
{
    return get_color("RED");
}

const float *View::DrawHelper::green()
{
    return get_color("GREEN");
}

const float *View::DrawHelper::blue()
{
    return get_color("BLUE");
}

const float *View::DrawHelper::yellow()
{
    return get_color("YELLOW");
}

const float *View::DrawHelper::black()
{
    return get_color("BLACK");
}

const float *View::DrawHelper::orange()
{
    return get_color("ORANGE");
}

const float *View::DrawHelper::grey()
{
    return get_color("GREY");
}

const float *View::DrawHelper::pink()
{
    return get_color("PINK");
}

const float *View::DrawHelper::cyan()
{
    return get_color("CYAN");
}
