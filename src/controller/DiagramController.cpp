//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "DiagramController.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/ServerReadyEvent.hpp"

std::string DiagramController::SERVICE = "DiagramService";

DiagramController::DiagramController(): ServiceProvider(DiagramController::SERVICE)
{
    ServiceContainer* service_container = ServiceContainer::get_instance();
    window_ = (Window *) service_container->get_service(Window::SERVICE);
    auto* event_manager = (EventManager *) service_container->get_service(EventManager::SERVICE);

    EventManager::Subscription server_ready = [this, &event_manager] (Event* e, const TypeUtil::Callback& unsubscribe) {
        auto* server_ready_event = (ServerReadyEvent*)e;

        Polygon polygon(server_ready_event->get_servers());
        voronoi_diagram_ = new VoronoiDiagram(polygon);
        voronoi_diagram_view_ = new VoronoiDiagramView(voronoi_diagram_);
        window_->addView(voronoi_diagram_view_);
    };

    event_manager->subscribe(EventType::SERVER_READY, server_ready);
}

