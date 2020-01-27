//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#ifndef DRONEPROJECT_POLYGONVIEW_HPP
#define DRONEPROJECT_POLYGONVIEW_HPP


#include "View.hpp"
#include "../model/Polygon.hpp"

class PolygonView: public View
{

public:

    explicit PolygonView(Polygon* polygon);

    void init(InputManager *input_manager, EventManager *event_manager, const TextureLoader &texture_loader) override;

    void start() override;

    void draw(DrawHelper *draw_helper) override;

    void quit() override;

private:

    Polygon* polygon_;
    std::string area_color_;
};


#endif //DRONEPROJECT_POLYGONVIEW_HPP
