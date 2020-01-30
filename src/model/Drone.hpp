//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_DRONE_HPP
#define DRONEPROJECT_DRONE_HPP


#include <string>
#include "Vector2D.hpp"
#include "../view/View.hpp"


class Drone
{

public:

    struct MoveData {
        int delta_time = 1;
        int radius = 100;
        float weight = 10;
        float temps = 0;
        float w = 1;
        float theta_zero = 10;
        float dx = 0;
        float dy = 0;
        float distance = 0;
        bool target_reached = false;
        bool circular_mode = false;
        Vector2D forces = {0,0};
        Vector2D acceleration = forces / weight;
        Vector2D speed = acceleration / (float) delta_time;
        Vector2D target = {0, 0};
    };

    explicit Drone(int id);

    int get_id() const;

    const std::string &get_server_name() const;

    void set_server_name(const std::string &server_name);

    Vector2D& get_position();

    MoveData &get_move_data();

    friend std::ostream& operator<<(std::ostream& os, const Drone& dt);

private:

    int id_;

    std::string server_name_;

    Vector2D position_;

    MoveData move_data_;


};


#endif //DRONEPROJECT_DRONE_HPP
