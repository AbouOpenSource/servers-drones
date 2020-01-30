//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERVIEW_HPP
#define DRONEPROJECT_SERVERVIEW_HPP


#include "../model/Server.hpp"
#include "TextureView.hpp"

class ServerView: public TextureView
{

public:

    explicit ServerView(Server* server);

    void start() override;

    void draw(DrawHelper* draw_helper) override;

    void init(DrawHelper *draw_helper, EventManager *event_manager) override;

private:

    Server* server_;
};


#endif //DRONEPROJECT_SERVERVIEW_HPP
