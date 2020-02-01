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
    /**
     * @brief data for the drone movement
     * @paragraph
     *  the drone movement is stored in this data structures.
     *  There are all requirements to allow Drone movement in its environment
     * @paragraph
     */
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

    /**
     * @brief this is the constructor of the drone, each drone have identifier in the system.
     * @param id identifier of the drone.
     * @details We use explicit for the compiler optimization.
     */
    explicit Drone(int id);
    /**
     * @brief getter of the identifier of the drone
     * @return the identifier of the drone.
     */
    int get_id() const;
    /**
     * @brief getter of the name of the server
     * @return the name of drone'server (string)
     * @details
     */
    const std::string &get_server_name() const;
    /**
     * @brief that is the setter of the drone'server name
     * @param server_name: the name of server where the drone is
     */
    void set_server_name(const std::string &server_name);

    const std::string &get_target_server_name() const;

    void set_target_server_name(const std::string &server_name);
  
    /**
     * @brief getter the position of the drone
     * @return: the position the drone Vector2D.
     */
    Vector2D& get_position();
    /**
     * @brief getter of the movement data of the drone
     * @return: a MoveData struct.
     */
    MoveData &get_move_data();

    /**
    * @brief overload of the cout operator for this class.
    * @param os the output stream.
    * @param dt the server to print.
    * @return the output stream.
    */
    friend std::ostream& operator<<(std::ostream& os, const Drone& dt);

private:

    int id_;

    std::string server_name_;

    std::string target_server_name_;

    Vector2D position_;

    MoveData move_data_;


};


#endif //DRONEPROJECT_DRONE_HPP
