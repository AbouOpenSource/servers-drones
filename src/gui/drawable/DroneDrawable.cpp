//
// Created by abou on 22/01/2020.
//

#include "DroneDrawable.hpp"
#include <iostream>

void DroneDrawable::start(InputManager *input_manager, Drawable::TextureLoader texture_loader)
{
    int lx = 0,ly=0;
   // droneId_ = texture_loader("../../../data/assets/drone.tga",lx,ly);
    std::cout<<"The id of drone: ";

    droneId_ = texture_loader("../data/assets/drone.tga",lx,ly);
    //assert(droneId_!=0);

    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void DroneDrawable::draw()
{

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,droneId_);
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

    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&droneId_));

}

DroneDrawable::DroneDrawable()
{
    droneId_=0;
}

DroneDrawable::DroneDrawable(Drone *drone):drone_(drone)
{
    droneId_=0;
}
