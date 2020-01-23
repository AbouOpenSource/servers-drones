//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_SERVER_HPP
#define DRONEPROJECT_SERVER_HPP


#include <vector>
#include "Vector2D.hpp"
#include "Drone.hpp"

enum Color { red, green, blue, pink, yellow, cyan };

class Server {

private:
    Vector2D speed_;
    Vector2D current_position_;
    std::vector<Drone*> the_drone_;
    float raduisDeCollision;
    int desiredNumberOfDrones;
    float dMax;
    const std::string name_;
    std::string color_;
//    Color color_;
    bool selected_ ;
public:
    /**
     *
     * @param speed
     * @param current_position it's a current position of the drone
     * @param the_drone
     */

    Server(std::string& name, Vector2D &current_position, std::string color);
//    Server(std::string& name, Vector2D &current_position, Color color);

    Server(const Vector2D &speed, const Vector2D &current_position, const std::vector<Drone*> &the_drone);

    const std::string &get_name() const;

    const Vector2D &getSpeed() const;

    const Vector2D &getCurrentPosition() const;

    const std::vector<Drone*> &getTheDrone() const;

    const float getRaduisDeCollision() const;

    void setSpeed(const Vector2D &speed);

    void setRaduisDeCollision(float raduis_de_collision);

    void setDesiredNumberOfDrones(int desired_number_of_drones);

    void setDMax(float d_max);

    void setCurrentPosition(const Vector2D &current_position);

    void setTheDrone(const std::vector<Drone*> &the_drone);

    void set_selected(bool selected);

    void detectCollision();

    int getCurrentNumberOfDrones();

    int getDesiredNumberOfDrones();

    bool is_selected() const;

    void connectDrone(Drone* ptrDrone);

    void disconnectDrone(Drone* ptrDrone);

    float getDMax() const;

    const std::string &get_color() const;

    void set_color(const std::string &color);

//    Color color_value_of(std::string color);
};


#endif //DRONEPROJECT_SERVER_HPP
