//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_DRONE_HPP
#define DRONEPROJECT_DRONE_HPP


#include "Vector2D.hpp"
#include "../view/View.hpp"

#include <string>

class Drone
{

public:

    explicit Drone(int id);

    int get_id() const;

    const string &get_server_name() const;

    void set_server_name(const string &server_name);

    Vector2D& get_position();

    friend std::ostream& operator<<(std::ostream& os, const Drone& dt);

private:

    int id_;

    std::string server_name_;

    Vector2D position_;
};


#endif //DRONEPROJECT_DRONE_HPP
