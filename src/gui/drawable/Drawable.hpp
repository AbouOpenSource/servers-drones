//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_DRAWABLE_HPP
#define DRONEPROJECT_DRAWABLE_HPP


#include "../../core/event/input/InputManager.hpp"

class Drawable
{

public:

    virtual void start(InputManager* input_manager);

    virtual void draw() const;

    virtual void quit();
};


#endif //DRONEPROJECT_DRAWABLE_HPP
