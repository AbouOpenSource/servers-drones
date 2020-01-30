//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_DRONEVIEW_HPP
#define DRONEPROJECT_DRONEVIEW_HPP


#include "../model/Drone.hpp"
#include "TextureView.hpp"
#include "../model/Server.hpp"

class DroneView: public TextureView
{

public:

    explicit DroneView(Drone* drone);

    void init(DrawHelper *draw_helper, EventManager *event_manager) override;

    void start() override;

    void draw(DrawHelper* draw_helper) override;

private:

    Drone* drone_;

    Server* server_;
};


#endif //DRONEPROJECT_DRONEVIEW_HPP
