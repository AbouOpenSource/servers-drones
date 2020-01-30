//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "DiagramController.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/ServerConfigChangeEvent.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"

std::string DiagramController::SERVICE = "DiagramService";

DiagramController::DiagramController()
    : Controller(DiagramController::SERVICE),
    window_((Window *) get_service(Window::SERVICE))
{
    event_manager_->subscribe(
            {EventType::SERVER_CONFIG_CHANGED, EventType::CONFIG_LOADED},
            [this] (Event* e, const EventManager::EventDetail& detail) {
        auto* server_config = (ServerConfigChangeEvent*)e;
        servers_ = server_config->get_servers();
        on_config_changed();
    });
}

void DiagramController::on_config_changed()
{
    for (auto* polygon: voronoi_diagram_.get_polygons()) {
        window_->removeView(polygon_views_[polygon]);
    }

    std::vector<Vector2D> points;

    points.reserve(servers_.size());
    for (Server* server: servers_) {
        points.push_back(server->get_position());
    }

    base_polygon_ = Polygon(points);
    base_polygon_.init();
    voronoi_diagram_ = VoronoiDiagram();
    voronoi_diagram_.init(&base_polygon_, Window::getWindowWidth(), Window::getWindowHeight());

    // Associates each polygon with its corresponding server.
    for (Polygon* polygon: voronoi_diagram_.get_polygons()) {
        for (Server *server: servers_) {
            // TODO is_inside not always working?
            if (polygon->is_inside(server->get_position())) {
                polygon_servers_[polygon] = server;
                break;
            }
        }
        polygon_views_[polygon] = new PolygonView(polygon, polygon_servers_[polygon]);
        window_->addView(polygon_views_[polygon]);
    }

    event_manager_->publish(EventType::DIAGRAM_CHANGED, new DiagramChangeEvent(this));
}


std::vector<Polygon *> &DiagramController::get_polygons()
{
    return voronoi_diagram_.get_polygons();
}

std::vector<Server *> DiagramController::get_servers()
{
    return servers_;
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
