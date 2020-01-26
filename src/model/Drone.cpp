#include "Drone.hpp"

#include "Circle.hpp"
#include "../core/ServiceContainer.hpp"
#include "../gui/Window.hpp"

//
// Created by abou on 19/12/2019.

Drone::Drone(const Vector2D &current_position, const Vector2D &forces, float weight)
        : current_position_(
        current_position), forces_(forces), weight_(weight), acceleration_(forces/weight),
          speed_(Vector2D(0,0))
{

}





Drone::Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
             Vector2D forces, float weight, std::string id) : current_position_(
        current_position), speed_(speed), acceleration_(acceleration), forces_(forces), weight_(weight), id_(id)
{}

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


void Drone::avoid_collision_with(Drone *ptrDrone)
{
    std::cout<<"Collision"<<std::endl;

    //TODO define the force to avoid the collison with the drone passing in args
    int ForceMAX = 200;
    float dAB = Drone::distance_with_other_drone(*ptrDrone);
    Vector2D BA =  Vector2D(
            Drone::current_position_.x_-ptrDrone->current_position_.x_ ,
             Drone::current_position_.y_-ptrDrone->current_position_.y_
    );


    if (dAB < 48 ) {
        Vector2D forceBA = ForceMAX * (BA / dAB);
        forces_=forceBA;
        //update_forces();
        update_acceleration();
        update_speed();

    } else {
        if(dAB<96)
        {
            Vector2D forceBA = (ForceMAX * (BA/dAB)) *   ((dAB- 96)/(48-96));
            forces_=forceBA;
            //update_forces();
            update_acceleration();
            update_speed();
        }
       }


}

float Drone::distance_with_other_drone(Drone item)
{
    float racine= sqrt((item.current_position_.x_ - Drone::current_position_.x_) * (item.current_position_.x_ - Drone::current_position_.x_)
         +
                               (item.current_position_.y_ - Drone::current_position_.y_) * (item.current_position_.y_ - Drone::current_position_.y_)
    );
    std::cout<<racine;
    return racine;
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

void Drone::addGoal(const Vector2D& item)
{
   // speed_= item+ speed_;
    target= item;
}

/**
 * the formula of acceleration computing
 */

void Drone::check_border(){

    /**
     *
     */
    ServiceContainer *container = ServiceContainer::get_instance();
    Window *window = (Window*) container->get_service(Window::SERVICE);

    /**
        * if we move to the border of the border up
        */
    if(abs(this->current_position_.y_- window->getWindowHeight())<100 && this->speed_.y_>0){
        this->acceleration_.y_=-this->acceleration_.y_;
        this->acceleration_.x_=-this->acceleration_.x_;
        this->speed_.y_ = -this->speed_.y_;

    }
    /**
     * if we move to the border of the border bottom
     */

    if(this->current_position_.y_<10 && this->speed_.y_<0){

        this->acceleration_.y_=-this->acceleration_.y_;
        this->acceleration_.x_=-this->acceleration_.x_;
        this->speed_.y_ = -this->speed_.y_;

    }
/**
 *
 */
    if(this->current_position_.x_<10 && this->speed_.x_<0){
        this->acceleration_.y_=-this->acceleration_.y_;
        this->acceleration_.x_=-this->acceleration_.x_;
        this->speed_.x_ = -this->speed_.x_;
    }
/**
 *
 */
    if(abs(this->current_position_.x_- window->getWindowWidth())<100 && this->speed_.x_>0){
        this->acceleration_.y_=-this->acceleration_.y_;
        this->acceleration_.x_=-this->acceleration_.x_;
        this->speed_.x_ = -this->speed_.x_;
    }
}


void Drone::update_acceleration()
{
   if(!target_is_get)
    acceleration_ = forces_ / weight_;
/**
 * Acceleration pour mouvement circulaire
 */
if (target_is_get){
    int radius =100;
    float thetaZero=0;
    float w=1;
    acceleration_.x_= -radius*(w*w)*cos(w*temps+thetaZero);
    acceleration_.y_= -radius*(w*w)*sin(w*temps+thetaZero);

}


}

void Drone::update_speed(){

    speed_ = 0.8*(speed_ + acceleration_);

}
void Drone::update_position()
{
    temps+=0.1;



    if(!target_is_get)

        current_position_ = current_position_ + speed_ ;
/**
 * Pour un mouvement circulaire
 */
    if(target_is_get){
        int radius = 100;
        float w = 1;
        float thetaZero=1000;
        current_position_.x_ = radius* cos(w*temps+thetaZero);
        current_position_.y_ = radius* sin(w*temps+thetaZero);
    }
}

void Drone::update_forces(){

    float dX=target.x_ - current_position_.x_;
    float dY=target.y_ - current_position_.y_;
        float distance = sqrt(dX*dX+dY*dY);
        if(distance > 60)
        forces_=Vector2D(target.x_-current_position_.x_,target.y_-current_position_.y_);
}

void Drone::assign_to_the_server(int serverId)
{
    this->serverId=serverId;
}

void Drone::i_get_target(bool value)
{
    target_is_get=true;
}


