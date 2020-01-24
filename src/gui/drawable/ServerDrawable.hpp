//
// Created by abou on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERDRAWABLE_HPP
#define DRONEPROJECT_SERVERDRAWABLE_HPP


#include "Drawable.hpp"
#include "../../model/Server.hpp"

class ServerDrawable: public Drawable
{

public:

    ServerDrawable();

    explicit ServerDrawable(Server* server);

    void init(InputManager *input_manager, EventManager* event_manager, const TextureLoader& texture_loader) override;

    void start() override;

    void draw() override;

    void quit() override;

    void detect_collision();
private:

    Server* server_;

    int serverTextureId_;
    int serverTextureWidth_;
    int serverTextureHeight_;
};


#endif //DRONEPROJECT_SERVERDRAWABLE_HPP
