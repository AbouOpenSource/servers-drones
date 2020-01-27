//
// Created by Maanrifa Bacar Ali on 26/01/2020.
//

#ifndef DRONEPROJECT_VORONOIDIAGRAMVIEW_HPP
#define DRONEPROJECT_VORONOIDIAGRAMVIEW_HPP


#include "View.hpp"
#include "../model/VoronoiDiagram.hpp"

class VoronoiDiagramView: public View
{

public:

    explicit VoronoiDiagramView(VoronoiDiagram *voronoi_diagram);

    void init(InputManager *input_manager, EventManager *event_manager, const TextureLoader &texture_loader) override;

    void start() override;

    void draw(DrawHelper *draw_helper) override;

    void quit() override;

private:

    VoronoiDiagram* voroinoi_diagram_;

};


#endif //DRONEPROJECT_VORONOIDIAGRAMVIEW_HPP
