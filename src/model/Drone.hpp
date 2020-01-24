//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_DRONE_HPP
#define DRONEPROJECT_DRONE_HPP


#include "Position.hpp"
#include "Vector2D.hpp"
#include "../view/View.hpp"
#include <math.h>

#include <string>

class Drone
{

public:

    explicit Drone(int id);

    void init(
            const Vector2D &current_position,
            const Vector2D& forces,
            float weight,
            const Vector2D &speed = {},
            const Vector2D &acceleration = {}
    );

    //Drone(const Vector2D &current_position, const Vector2D &forces, float weight);

    int get_id() const;

    const string &get_server_name() const;

    void set_server_name(const string &server_name);

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

    void avoid_collision_with(Drone* drone);

    float distance_from(Drone* item);

    void add_target(Vector2D item);

    friend std::ostream& operator<<(std::ostream& os, const Drone& dt);

private:

    int delta_time_;
    int id_;

    float weight_;

    std::string server_name_;

    Vector2D current_position_;
    Vector2D speed_;
    Vector2D acceleration_;
    Vector2D forces_;
};


#endif //DRONEPROJECT_DRONE_HPP
