//
// Created by abou on 19/12/2019.
//

#include "Drone.hpp"
#include "Circle.hpp"
#include <glutWindow.h>


Drone::Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
             Vector2D forces, float weight, std::string id) : current_position_(
        current_position), speed_(speed), acceleration_(acceleration), forces_(forces), weight_(weight), id_(id)
{

}

const Vector2D &Drone::get_current_position() const
{
    return current_position_;
}

const Vector2D &Drone::get_speed() const
{
    return speed_;
}

const Vector2D &Drone::get_acceleration() const
{
    return acceleration_;
}

void Drone::set_current_position(const Vector2D &current_position)
{
    current_position_ = current_position;
}

void Drone::set_speed(const Vector2D &speed)
{
    speed_ = speed;
}

void Drone::set_acceleration(const Vector2D &acceleration)
{
    acceleration_ = acceleration;
}


void Drone::set_forces(const Vector2D &forces)
{
    forces_ = forces;
}

const Vector2D &Drone::get_forces() const
{
    return forces_;
}

void Drone::set_weight(float weight)
{
    Drone::weight_ = weight;
}

Drone::Drone(const Vector2D &current_position, const Vector2D &forces, float weight)
        : current_position_(
        current_position), forces_(forces), weight_(weight), acceleration_(forces / weight),
          speed_((forces / weight) / delta_time)
{

}

void Drone::update_position()
{
    current_position_ = current_position_ + speed_ / delta_time;
}

void Drone::avoid_collision_with(Drone *ptrDrone)
{
    //TODO define the force to avoid the collison with the drone passing in args

    int ForceMAX = 10;
    //float dAB = this->distanceWithOtherDrone(*ptrDrone);
    //Computing of the
    Vector2D *BA = new Vector2D(
            Drone::current_position_.x_ - ptrDrone->current_position_.x_,
            Drone::current_position_.y_ - ptrDrone->current_position_.y_
    );


    float distance = Drone::distance_with_other_drone(*ptrDrone);
    //10 raduis
    if (distance < 10) {
        //First case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()

    } else {
        //Second case
        //         Vector2D forceBA = ForceMAX * (BA/dAB) *(dAB- dMax)/Circle::getRaduis()


    }

}

float Drone::distance_with_other_drone(Drone item)
{
    return
            sqrt(item.current_position_.x_ - Drone::current_position_.x_ *
                                                  item.current_position_.x_ -
                 Drone::current_position_.x_
                 +
                         item.current_position_.y_ - Drone::current_position_.y_ *
                                                  item.current_position_.y_ -
                 Drone::current_position_.y_
            );
}

void Drone::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f,1.0f,1.0f);
    glBindTexture(GL_TEXTURE_2D,droneId);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(1200.0,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(1200.0,675.0);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0,675.0);
    glEnd();








}

void Drone::quit()
{



}

void Drone::start(InputManager *input_manager,TextureLoader texture_loader)
{
    int lx,ly;
   // droneId = GlutWindow::loadTGATexture("/home/abou/Bureau/COURSM1IOT/AdvancedAlgorithms/FinalProject/drones-servers/data/assets/drone.tga",lx,ly);
    assert(droneId!=0);
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Drone::Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration, const Vector2D& forces,
             float weight):current_position_(current_position),speed_(speed),acceleration_(acceleration),forces_(forces),weight_(weight)
{

}

std::ostream &operator << (std::ostream &os, const Drone &dt)
{
    os <<"My position :"<< dt.get_current_position().x_ << '/' << dt.get_current_position().y_ << '/' ;
    return os;
}

void Drone::addGoal(Vector2D item)
{

}



