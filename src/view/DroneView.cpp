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
    //auto &data = drone_->get_move_data();
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glPushMatrix();
    glTranslatef(drone_->get_position().x_-48, drone_->get_position().y_-48, 1.0);
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
/*
    glDisable(GL_TEXTURE_2D);
    glColor3fv(draw_helper->black());
    glPushMatrix();
    glTranslatef(drone_->get_position().x_,drone_->get_position().x_,0);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);*/
    //float a=0.0;
    // float a = (float) (atan(data.speed.x_/data.speed.y_) + M_PI_2);
    /*for (int i=0; i<21; i++) {
        glVertex2f(100*cos(a),100*sin(a));
        a+=(float)(M_PI/20.0);
    }
    glEnd();
    glLineWidth(1);
    glPopMatrix();
*/






}
