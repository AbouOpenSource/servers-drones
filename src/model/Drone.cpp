#include "Drone.hpp"

#include "Circle.hpp"

//
// Created by abou on 19/12/2019.
Drone::Drone(const Vector2D &current_position, const Vector2D &forces, float weight)
        : current_position_(
        current_position), forces_(forces), weight_(weight), acceleration_(forces / weight),
          speed_((forces / weight) / delta_time)
{

}
//

#define D_MAX 96

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

void Drone::update_position()
{
    current_position_ = current_position_ + (speed_ / delta_time);
}

void Drone::avoid_collision_with(Drone *ptrDrone)
{
    //TODO define the force to avoid the collison with the drone passing in args

    int ForceMAX = 15000;
    Vector2D *BA = new Vector2D(
             ptrDrone->current_position_.x_-Drone::current_position_.x_ ,
             Drone::current_position_.x_ -Drone::current_position_.y_
    );

    float dAB = Drone::distance_with_other_drone(*ptrDrone);
    if (dAB < 96) {
        //First case
         Vector2D forceBA = ForceMAX * (*BA / dAB);
        forces_=forceBA;
        std::cout<<forces_<<std::endl;
        update_acceleration();
       // update_speed();

    } else {
        //Second case
       Vector2D forceBA = (ForceMAX * (*BA/dAB)) *   ((dAB- 96)/(48-96));
        forces_=forceBA;
        update_acceleration();
        update_speed();
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
    speed_= item+ speed_;
}

/**
 * the formula of acceleration computing
 */
void Drone::update_acceleration()
{
    acceleration_ = forces_ / weight_;
}
void Drone::check_border(){

    if(abs(this->current_position_.x_-1000)<900 || abs(1000-this->current_position_.x_)<100 ){
      //  std::cout<<"first condition of border";
        this->speed_.x_ = -this->speed_.x_;
    }

    if(abs(this->current_position_.y_-800)<700|| abs(1000-this->current_position_.y_)<100 ){
       // std::cout<<"second condition of border";
        this->speed_.x_ = -this->speed_.x_;
    }

}

void Drone::update_speed(){
    std::cout << "The speed" << speed_ <<"The acceleration" <<acceleration_<<endl;
    speed_ = (speed_ + acceleration_);
}


