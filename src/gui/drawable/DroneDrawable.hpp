//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_DRONEDRAWABLE_HPP
#define DRONEPROJECT_DRONEDRAWABLE_HPP


#include "Drawable.hpp"
#include "../../model/Drone.hpp"

class DroneDrawable: public Drawable
{
private:
    int droneId_{};
    Drone *drone_{};

public:
    DroneDrawable();
    explicit DroneDrawable(Drone * drone);

    void start(InputManager *input_manager, TextureLoader texture_loader) override;

    void draw() override;

    void quit() override;

};


#endif //DRONEPROJECT_DRONEDRAWABLE_HPP
