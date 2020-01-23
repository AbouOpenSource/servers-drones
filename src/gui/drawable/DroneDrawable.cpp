//
// Created by abou on 22/01/2020.
//

#include "DroneDrawable.hpp"
#include <iostream>

DroneDrawable::DroneDrawable() : droneTextureId_(0)
{}

DroneDrawable::DroneDrawable(Drone *drone): drone_(drone), droneTextureId_(0)
{}

void DroneDrawable::init(
        InputManager *input_manager,
        EventManager* event_manager,
        const Drawable::TextureLoader& texture_loader)
{
    droneTextureId_ = texture_loader("drone", droneTextureWidth_, droneTextureHeight_);
}

void DroneDrawable::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DroneDrawable::draw()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, droneTextureId_);
    glPushMatrix();
    glTranslatef(drone_->get_current_position().x_,drone_->get_current_position().y_,1.0);
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
    std::cout<< *drone_<< std::endl;
    drone_->update_position();
}

void DroneDrawable::quit()
{
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&droneTextureId_));
}
