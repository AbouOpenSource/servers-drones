//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_DRONE_HPP
#define DRONEPROJECT_DRONE_HPP


#include "Position.hpp"
#include "Vector2D.hpp"
#include <math.h>

//why
//#include "Server.hpp"
#include <string>

//enum Color { RED, GREEN, BLUE, PINK, YELLOW, CYAN };

class Drone {

    Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration, Vector2D forces,
          float weight ,std::string name);


private:
    Drone(const Vector2D &current_position, const Vector2D &forces, float weight);

    std::string name_;
    Vector2D current_position_;
    Vector2D speed_;
    Vector2D acceleration_;
    Vector2D forces_;
    float weight_;
    int delta_time = int(3);
    //Server my_server_;

public:

    Drone(const Vector2D &current_position, const Vector2D &speed, const Vector2D &acceleration,
          Vector2D forces, float weight);

    const Vector2D &get_current_position() const;

    const Vector2D &get_speed() const;

    const Vector2D &get_acceleration() const;

    const Vector2D &get_forces() const;

    void set_current_position(const Vector2D &current_position);

    void set_speed(const Vector2D &speed);

    void set_acceleration(const Vector2D &acceleration);

    void set_forces(const Vector2D &forces);

    void set_weight(float weight);

    void update_position();

    void avoid_collision_with(Drone *ptrDrone);

    float distance_with_other_drone(Drone item);
};


#endif //DRONEPROJECT_DRONE_HPP
