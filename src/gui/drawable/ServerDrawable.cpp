//
// Created by abou on 22/01/2020.
//

#include <iostream>
#include "ServerDrawable.hpp"

void ServerDrawable::start(InputManager *input_manager, Drawable::TextureLoader texture_loader)
{
    int lx = 0,ly=0;
    serverId_ = texture_loader("../data/assets/server.tga",lx,ly);
    std::cout<<"lx : "<<lx<<" ly"<< ly<< std::endl;
    assert(serverId_!=0);
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void ServerDrawable::draw()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,serverId_);
    glPushMatrix();
    glTranslatef(server_.getCurrentPosition().x_,server_.getCurrentPosition().y_,1.0);
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
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&serverId_));
}
