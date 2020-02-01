//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_DIAGRAMCONTROLLER_HPP
#define DRONEPROJECT_DIAGRAMCONTROLLER_HPP


#include "../model/VoronoiDiagram.hpp"
#include "../model/MyPolygon.hpp"
#include "../view/PolygonView.hpp"
#include "../Window.hpp"
#include "Controller.hpp"

class DiagramController: public Controller
{

public:

    static std::string SERVICE;

    DiagramController();

    std::vector<MyPolygon*>& get_polygons();

    std::vector<Server*> get_servers();

    MyPolygon* get_polygon_for_server(Server* server);

    Server* get_server_for_polygon(MyPolygon* polygon);

    bool are_polygons_neighbors(MyPolygon* p1, MyPolygon* p2);

    float get_server_area(Server* server);

    float get_total_area();

private:

    void on_config_changed();

    Window* window_;

    VoronoiDiagram voronoi_diagram_;

    MyPolygon base_polygon_;

    std::vector<Server*> servers_;

    std::map<MyPolygon*, PolygonView*> polygon_views_;

    std::map<MyPolygon*, Server*> polygon_servers_;

};


#endif //DRONEPROJECT_DIAGRAMCONTROLLER_HPP
