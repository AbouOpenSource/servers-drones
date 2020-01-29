//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_SERVER_HPP
#define DRONEPROJECT_SERVER_HPP


#include <vector>
#include <ostream>
#include "Vector2D.hpp"
#include "Drone.hpp"

class Server {

public:

    Server(const std::string& name, const std::string& color);

    bool is_selected() const;

    void set_selected(bool selected);

    Vector2D& get_position();

    const std::string &get_name() const;

    const std::string &get_color() const;

    void set_color(const std::string &color);

    friend std::ostream &operator<<(std::ostream &os, const Server &server);

private:

    bool selected_;

    Vector2D position_;

    std::string name_;
    std::string color_;
};


#endif //DRONEPROJECT_SERVER_HPP
