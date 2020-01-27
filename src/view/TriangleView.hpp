//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_TRIANGLEVIEW_HPP
#define DRONEPROJECT_TRIANGLEVIEW_HPP

#include "View.hpp"
#include "../model/Triangle.hpp"

class TriangleView: public View
{

public:

    TriangleView(Triangle* triangle);

    void init(InputManager *input_manager, EventManager *event_manager, const TextureLoader &texture_loader) override;

    void start() override;

    void draw(DrawHelper *draw_helper) override;

    void draw_circle();

    void quit() override;

private:

    Triangle* triangle_;
};


#endif //DRONEPROJECT_TRIANGLEVIEW_HPP
