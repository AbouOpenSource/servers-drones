//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERVIEW_HPP
#define DRONEPROJECT_SERVERVIEW_HPP


#include "../model/Server.hpp"
#include "TextureView.hpp"
#include "../controller/DiagramController.hpp"
#include "../controller/ZoneController.hpp"

class ServerView: public TextureView
{

public:

    explicit ServerView(Server* server);

    void start() override;

    void draw(DrawHelper* draw_helper) override;

    void init(DrawHelper *draw_helper, ServiceContainer *service_container) override;

private:

    Server* server_;

    DiagramController* diagram_controller_;

    ZoneController* zone_controller_;
};


#endif //DRONEPROJECT_SERVERVIEW_HPP
