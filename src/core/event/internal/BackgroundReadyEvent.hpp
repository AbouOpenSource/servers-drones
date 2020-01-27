//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_BACKGROUNDREADYEVENT_HPP
#define DRONEPROJECT_BACKGROUNDREADYEVENT_HPP


#include "../Event.hpp"
#include "../../../model/Polygon.hpp"
#include "../../../model/VoronoiDiagram.hpp"

class BackgroundReadyEvent: public Event
{

public:

    BackgroundReadyEvent(VoronoiDiagram* voronoi_diagram);

    VoronoiDiagram *get_voronoi_diagram() const;

private:

    VoronoiDiagram* voronoi_diagram_;

};


#endif //DRONEPROJECT_BACKGROUNDREADYEVENT_HPP
