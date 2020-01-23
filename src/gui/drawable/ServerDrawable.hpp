//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERDRAWABLE_HPP
#define DRONEPROJECT_SERVERDRAWABLE_HPP


#include "Drawable.hpp"
#include "../../model/Server.hpp"
#include <cassert>

class ServerDrawable: public Drawable
{

    Server server_;
   int serverId_;
public:
    void start(InputManager *input_manager, TextureLoader texture_loader) override;

    void draw() override;

    void quit() override;
};


#endif //DRONEPROJECT_SERVERDRAWABLE_HPP
