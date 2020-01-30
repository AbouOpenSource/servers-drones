//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "View.hpp"

std::vector<std::string> View::DrawHelper::COLORS = {"GREEN", "PINK", "ORANGE", "BLUE", "GREY", "YELLOW", "CYAN", "BLACK", "RED"};

View::View()
= default;

void View::init(DrawHelper *draw_helper, EventManager *event_manager)
{}

void View::start()
{}

void View::draw(DrawHelper* draw_helper)
{}

void View::quit()
{}

View::DrawHelper::DrawHelper()
{}

void View::DrawHelper::init(View::TextureLoader* texture_loader, View::TextWriter * text_writer)
{
    texture_loader_ = texture_loader;
    text_writer_ = text_writer;
}

const float * View::DrawHelper::get_color(const std::string &color_name)
{
    std::cout << "Color: " << color_name << std::endl;

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

int View::DrawHelper::load_texture(const std::string &file_name, int &width, int &height)
{
    return (*texture_loader_)(file_name, width, height);
}

void View::DrawHelper::write_text(const std::string &text, int x, int y, View::WriteOptions opts)
{
    (*text_writer_)(text, x, y, opts);
}
