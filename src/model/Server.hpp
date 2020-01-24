//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_SERVER_HPP
#define DRONEPROJECT_SERVER_HPP


#include <vector>
#include "Vector2D.hpp"
#include "Drone.hpp"

class Server {

public:

    Server(std::string& name, std::string& color);

    const std::string &get_name() const;

    const Vector2D &get_position() const;

    float get_collision_radius() const;

    void set_collision_radius(float collision_radius);

    void set_expected_drone_count(int expected_drone_count);

    void set_d_max(float d_max);

    void set_current_position(const Vector2D &current_position);

    void set_selected(bool selected);

    int get_expected_drone_count();

    bool is_selected() const;

    float get_d_max() const;

    const std::string &get_color() const;

    void set_color(const std::string &color);

private:

    int expected_drone_count_;

    float collision_radius_;
    float d_max_;

    bool selected_;

    Vector2D current_position_;

    std::string name_;
    std::string color_;
};


#endif //DRONEPROJECT_SERVER_HPP
