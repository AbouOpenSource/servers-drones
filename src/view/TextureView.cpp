//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#include "TextureView.hpp"

TextureView::TextureView(const std::string &file_name)
    : View(), texture_id_(0), texture_height_(0), texture_width_(0), file_name_(file_name)
{}

void TextureView::init(DrawHelper* draw_helper, ServiceContainer *service_container)
{
    texture_id_ = draw_helper->load_texture(file_name_, texture_width_, texture_height_);
}

void TextureView::draw(DrawHelper* draw_helper)
{
    View::draw(draw_helper);
}

void TextureView::start()
{
    View::start();
}

void TextureView::quit()
{
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&texture_id_));
}
