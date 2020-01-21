//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_DRAWABLE_HPP
#define DRONEPROJECT_DRAWABLE_HPP

#include "../../core/event/input/InputManager.hpp"

class Drawable
{

public:

    typedef std::function<int(const std::string& path, int& x, int& y)> TextureLoader;

    Drawable();

    virtual void start(InputManager* input_manager, TextureLoader texture_loader);

    virtual void draw();

    virtual void quit();
};


#endif //DRONEPROJECT_DRAWABLE_HPP
