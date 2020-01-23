//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_DRONEDRAWABLE_HPP
#define DRONEPROJECT_DRONEDRAWABLE_HPP


#include "Drawable.hpp"
#include "../../model/Drone.hpp"

class DroneDrawable: public Drawable
{

public:

    DroneDrawable();

    explicit DroneDrawable(Drone* drone);

    void init(InputManager *input_manager, EventManager* event_manager, const TextureLoader& texture_loader) override;

    void start() override;

    void draw() override;

    void quit() override;

private:

    Drone* drone_;

    int droneTextureId_{};
    int droneTextureWidth_;
    int droneTextureHeight_;
};


#endif //DRONEPROJECT_DRONEDRAWABLE_HPP
