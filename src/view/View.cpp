//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "View.hpp"
#include "../util/StringUtil.hpp"
#include "../util/VectorUtil.hpp"

std::vector<std::string> View::DrawHelper::COLORS = {
        "GREEN",
        "PINK",
        "ORANGE",
        "BLUE",
        "GREY",
        "YELLOW",
        "CYAN",
        "BROWN",
        "RED",
        "MAGENTA",
        "PURPLE"
};

View::View()
= default;

void View::init(DrawHelper *draw_helper, ServiceContainer *service_container)
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

const float * View::DrawHelper::parse(const std::string &color_name)
{
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
	if (color_name == "WHITE") {
        return WHITE;
    }
	if (color_name == "MAGENTA") {
        return MAGENTA;
    }
	if (color_name == "BROWN") {
        return BROWN;
    }
	if (color_name == "PURPLE") {
        return PURPLE;
    }

    return parse_dynamic_color(color_name);
}

const float *View::DrawHelper::red()
{
    return parse("RED");
}

const float *View::DrawHelper::green()
{
    return parse("GREEN");
}

const float *View::DrawHelper::blue()
{
    return parse("BLUE");
}

const float *View::DrawHelper::yellow()
{
    return parse("YELLOW");
}

const float *View::DrawHelper::black()
{
    return parse("BLACK");
}

const float *View::DrawHelper::orange()
{
    return parse("ORANGE");
}

const float *View::DrawHelper::grey()
{
    return parse("GREY");
}

const float *View::DrawHelper::pink()
{
    return parse("PINK");
}

const float *View::DrawHelper::cyan()
{
    return parse("CYAN");
}

const float *View::DrawHelper::white()
{
    return parse("WHITE");
}

const float *View::DrawHelper::dynamic_color()
{
    float r = random_float();
    float g = random_float();
    float b = random_float();
    return push_dynamic_color(std::to_string(r) + ':' + std::to_string(g) + ':' + std::to_string(b), r, g, b);
}

const std::string View::DrawHelper::dynamic_color_string()
{
    auto* color = dynamic_color();

    for (auto& it: colors_) {
        if (it.second == color) {
            return it.first;
        }
    }

    return "YELLOW";
}

const float *View::DrawHelper::parse_dynamic_color(const std::string &color)
{
    auto s = StringUtil::split(color, ':');
    auto r = std::strtof(s[0].c_str(), nullptr);
    auto g = std::strtof(s[1].c_str(), nullptr);
    auto b = std::strtof(s[2].c_str(), nullptr);
    return push_dynamic_color(color, r, g, b);
}

const float* View::DrawHelper::push_dynamic_color(const std::string &color, float r, float g, float b)
{
    for (auto& it: colors_) {
        if (it.first == color) {
            return it.second;
        }
    }
    colors_[color] = new (float[4]){r, g, b, 1.0f};

    return colors_[color];
}

int View::DrawHelper::load_texture(const std::string &file_name, int &width, int &height)
{
    return (*texture_loader_)(file_name, width, height);
}

void View::DrawHelper::write_text(const std::string &text, int x, int y, View::WriteOptions opts)
{
    (*text_writer_)(text, x, y, opts);
}

float View::DrawHelper::random_float()
{
    return std::rand() / (RAND_MAX + 1.);
}

View::DrawHelper::~DrawHelper()
{
    for (auto& it: colors_) {
        delete it.second;
    }
}
