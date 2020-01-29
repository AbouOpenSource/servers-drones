//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "DiagramController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/ServerConfigChangeEvent.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"

std::string DiagramController::SERVICE = "DiagramService";

DiagramController::DiagramController()
    : Controller(DiagramController::SERVICE)
{
    auto* window = (Window *) get_service(Window::SERVICE);

    event_manager_->subscribe(
            {EventType::SERVER_CONFIG_CHANGED, EventType::CONFIG_LOADED},
            [this, window] (Event* e, const EventManager::EventDetail& detail) {
        auto* server_config = (ServerConfigChangeEvent*)e;
        on_data_changed(server_config->get_servers(), window);
    });
}

void DiagramController::on_data_changed(const std::vector<Server*>& servers, Window* window)
{
    std::vector<Vector2D> points;

    points.reserve(servers.size());
    for (Server* server: servers) {
        points.push_back(server->get_position());
    }

    base_polygon_ = Polygon(points);
    base_polygon_.init();
    voronoi_diagram_ = VoronoiDiagram();
    voronoi_diagram_.init(&base_polygon_, Window::getWindowWidth(), Window::getWindowHeight());

    // Associates each polygon with its corresponding server.
    for (Polygon* polygon: voronoi_diagram_.get_polygons()) {
        for (Server *server: servers) {
            // TODO is_inside not always working?
            if (polygon->is_inside(server->get_position())) {
                polygon_servers_[polygon] = server;
                break;
            }
        }
        polygon_views_[polygon] = new PolygonView(polygon, polygon_servers_[polygon]);
        window->addView(polygon_views_[polygon]);
    }

    event_manager_->publish(EventType::DIAGRAM_CHANGED, new DiagramChangeEvent(this));
}


std::vector<Polygon *> &DiagramController::get_polygons()
{
    return voronoi_diagram_.get_polygons();
}

Polygon *DiagramController::get_polygon_for_server(Server *server)
{
    for (auto& it: polygon_servers_) {
        if (it.second == server) {
            return it.first;
        }
    }
    return nullptr;
}

Server *DiagramController::get_server_for_polygon(Polygon *polygon)
{
    return polygon_servers_[polygon];
}