//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "BackgroundReadyEvent.hpp"

BackgroundReadyEvent::BackgroundReadyEvent(VoronoiDiagram* voronoi_diagram)
    : Event("Background is ready"),
    voronoi_diagram_(voronoi_diagram)
{}

VoronoiDiagram *BackgroundReadyEvent::get_voronoi_diagram() const
{
    return voronoi_diagram_;
}
