//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_DIAGRAMCONTROLLER_HPP
#define DRONEPROJECT_DIAGRAMCONTROLLER_HPP


#include "../core/service/ServiceProvider.hpp"
#include "../model/VoronoiDiagram.hpp"
#include "../model/Polygon.hpp"
#include "../view/PolygonView.hpp"
#include "../Window.hpp"
#include "ServerController.hpp"
#include "../view/VoronoiDiagramView.hpp"

class DiagramController: public ServiceProvider
{

public:

    static std::string SERVICE;

    DiagramController();

private:

    VoronoiDiagram* voronoi_diagram_;

    Window* window_;

    std::map<Polygon*, PolygonView*> polygon_view_;
    std::map<Polygon*, Server*> polygon_server_;
};


#endif //DRONEPROJECT_DIAGRAMCONTROLLER_HPP
