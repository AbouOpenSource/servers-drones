//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_DRAWABLE_HPP
#define DRONEPROJECT_DRAWABLE_HPP

#include "../../core/event/input/InputManager.hpp"
#include "../../core/event/EventManager.hpp"

class Drawable
{

public:

    typedef std::function<int(const std::string& path, int& x, int& y)> TextureLoader;

    Drawable();

    virtual void init(InputManager* input_manager, EventManager* event_manager, TextureLoader texture_loader);

    virtual void start();

    virtual void draw();

    virtual void quit();
};


#endif //DRONEPROJECT_DRAWABLE_HPP
