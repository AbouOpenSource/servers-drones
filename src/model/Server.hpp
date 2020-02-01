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
    /**
     *
     * @param name: server name, in our case it's a city name like : Paris, Berlin
     * @param color
     */
    Server(const std::string& name, const std::string& color);
    /**
     * @brief check if the server is selected
     * @return true or false.
     */
    bool is_selected() const;
    /**
     * @brief setter of the selecting of the server.
     * @param selected true for selected and else false.
     */
    void set_selected(bool selected);
    /**
     * @brief getter of the position of the server.
     * @return Vector2D
     */
    Vector2D& get_position();
    /**
     * @brief setter of name of the server.
     * @return string of the name of the server
     */
    const std::string &get_name() const;
    /**
     * @brief getter of the color.
     * @return string of the color of the zone of server
     */
    const std::string &get_color() const;
    /**
     * @brief setter of the color of server.
     * @param color
     */
    void set_color(const std::string &color);
    /**
     * @brief overload of the cout operator for this class.
     * @param os the output stream.
     * @param server the server to print.
     * @return the output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Server &server);

private:

    bool selected_;

    Vector2D position_;

    std::string name_;
    std::string color_;
};


#endif //DRONEPROJECT_SERVER_HPP
