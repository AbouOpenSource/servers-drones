//
// Created by Maanrifa Bacar Ali on 26/01/2020.
//

#include "VoronoiDiagramView.hpp"

VoronoiDiagramView::VoronoiDiagramView(VoronoiDiagram *voronoi_diagram): voroinoi_diagram_(voronoi_diagram)
{}

void VoronoiDiagramView::init(InputManager *input_manager, EventManager *event_manager,
                              const View::TextureLoader &texture_loader)
{
    View::init(input_manager, event_manager, texture_loader);
}

void VoronoiDiagramView::start()
{
    View::start();
}

void VoronoiDiagramView::draw(View::DrawHelper *draw_helper)
{
    for (Polygon* polygon: voroinoi_diagram_->get_polygons()) {
        polygon->draw(draw_helper);
    }
}

void VoronoiDiagramView::quit()
{
    View::quit();
}

