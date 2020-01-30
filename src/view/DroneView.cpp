//
// Created by abou on 22/01/2020.
//

#include "DroneView.hpp"

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
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glPushMatrix();
    glTranslatef(drone_->get_position().x_ ICON_MARGIN, drone_->get_position().y_ ICON_MARGIN, 1.0);
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
}
