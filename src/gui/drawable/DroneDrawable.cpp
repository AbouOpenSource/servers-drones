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
    GlutWindow::drawText(drone_->get_current_position().x_, drone_->get_current_position().y_, "speed : x= " +to_string( drone_->get_speed().x_)+" y= "+to_string(drone_->get_speed().y_), GlutWindow::ALIGN_RIGHT, GLUT_BITMAP_8_BY_13);
    glDisable(GL_TEXTURE_2D);
    float deltax=(drone_->target.x_ - drone_->get_current_position().x_);
    float deltay=(drone_->target.y_ - drone_->get_current_position().y_);
    float distance =sqrt(deltax*deltax+deltay*deltay);
/*
    if(distance<20){
        drone_->set_forces(Vector2D(0,0));
        drone_->i_get_target(true);
 }
    if(distance<10){
        drone_->i_get_target(true);
    }
*/

    update_position();


}

void DroneDrawable::quit()
{
    glDeleteTextures(1, reinterpret_cast<const GLuint *>(&droneTextureId_));
}

void DroneDrawable::avoid_collision_with_drone(Drone *item)
{
    drone_->avoid_collision_with(item);
}

void DroneDrawable::update_position()
{
    drone_->update_forces();
    drone_->update_acceleration();
    drone_->update_speed();
    drone_->update_position();
}
