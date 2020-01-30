//
// Created by abou on 22/01/2020.
//

#include "ServerView.hpp"

ServerView::ServerView(Server *server): TextureView("master"), server_(server)
{}

void ServerView::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ServerView::draw(DrawHelper* draw_helper)
{
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glPushMatrix();
    glTranslatef(server_->get_position().x_ ICON_MARGIN, server_->get_position().y_ ICON_MARGIN, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(ICON_SIZE,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(ICON_SIZE, ICON_SIZE);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0, ICON_SIZE);
    glEnd();
    glPopMatrix();
    draw_helper->write_text(server_->get_name(), server_->get_position().x_, server_->get_position().y_);
}
