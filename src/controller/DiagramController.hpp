//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_DIAGRAMCONTROLLER_HPP
#define DRONEPROJECT_DIAGRAMCONTROLLER_HPP


#include "../model/VoronoiDiagram.hpp"
#include "../model/Polygon.hpp"
#include "../view/PolygonView.hpp"
#include "../Window.hpp"
#include "Controller.hpp"

class DiagramController: public Controller
{

public:

    static std::string SERVICE;

    DiagramController();

    std::vector<Polygon*>& get_polygons();

    Polygon* get_polygon_for_server(Server* server);

    Server* get_server_for_polygon(Polygon* polygon);

private:

    void on_data_changed(const std::vector<Server*>& servers, Window* window);

    VoronoiDiagram voronoi_diagram_;

    Polygon base_polygon_;

    std::map<Polygon*, PolygonView*> polygon_views_;

    std::map<Polygon*, Server*> polygon_servers_;

};


#endif //DRONEPROJECT_DIAGRAMCONTROLLER_HPP
