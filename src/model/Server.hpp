//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_SERVER_HPP
#define DRONEPROJECT_SERVER_HPP


#include <vector>
#include "Vector2D.hpp"
#include "Drone.hpp"

class Server {

private:
    Vector2D speed_;
    Vector2D current_position_;
    std::vector<Drone*> the_drone_;
    float raduisDeCollision;
    int desiredNumberOfDrones;
    float dMax;
//public:
    /**
     *
     * @param speed
     * @param current_position it's a current position of the drone
     * @param the_drone
     */

    Server(const Vector2D &speed, const Vector2D &current_position, const std::vector<Drone*> &the_drone);

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

    void detectCollision();

    int getCurrentNumberOfDrones();

    int getDesiredNumberOfDrones();

  void connectDrone(Drone* ptrDrone);

   void disconnectDrone(Drone* ptrDrone);

    float getDMax() const;

};


#endif //DRONEPROJECT_SERVER_HPP
