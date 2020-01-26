//
// Created by abou on 22/01/2020.
//

#include "DroneView.hpp"
#include <iostream>

DroneView::DroneView(Drone *drone): TextureView("drone"), drone_(drone)
{}

void DroneView::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DroneView::draw(DrawHelper* draw_helper)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
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
    drone_->update();
}
