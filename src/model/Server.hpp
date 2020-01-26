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

    bool is_selected() const;

    void set_selected(bool selected);

    Vector2D& get_position();

    const string &get_name() const;

    const string &get_color() const;

    void set_color(const string &color);

private:

    bool selected_;

    Vector2D position_;

    std::string name_;
    std::string color_;
};


#endif //DRONEPROJECT_SERVER_HPP
