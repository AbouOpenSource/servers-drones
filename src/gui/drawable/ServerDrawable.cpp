//
// Created by abou on 22/01/2020.
//

#include <iostream>
#include "ServerDrawable.hpp"

ServerDrawable::ServerDrawable() : serverTextureId_(0)
{}

ServerDrawable::ServerDrawable(Server *server): server_(server), serverTextureId_(0)
{}

void ServerDrawable::init(
        InputManager *input_manager,
        EventManager *event_manager,
        const Drawable::TextureLoader &texture_loader)
{
    serverTextureId_ = texture_loader("server", serverTextureWidth_, serverTextureHeight_);
}

void ServerDrawable::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ServerDrawable::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, serverTextureId_);
    glPushMatrix();
    glTranslatef(server_->getCurrentPosition().x_,server_->getCurrentPosition().y_,1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);

    glTexCoord2f(1.0,0.0);
    glVertex2f(96.0,0.0);

    glTexCoord2f(1.0,1.0);
    glVertex2f(96.0,96.0);

    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,96.0);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void ServerDrawable::quit()
{
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&serverTextureId_));
}
