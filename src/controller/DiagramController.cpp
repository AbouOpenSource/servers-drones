//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "DiagramController.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/ServerReadyEvent.hpp"
#include "../core/event/internal/BackgroundReadyEvent.hpp"

std::string DiagramController::SERVICE = "DiagramService";

DiagramController::DiagramController(): ServiceProvider(DiagramController::SERVICE)
{
    ServiceContainer* service_container = ServiceContainer::get_instance();
    window_ = (Window *) service_container->get_service(Window::SERVICE);
    auto* event_manager = (EventManager *) service_container->get_service(EventManager::SERVICE);

    EventManager::Subscription server_ready = [this, event_manager] (Event* e, const TypeUtil::Callback& unsubscribe) {
        auto* server_ready_event = (ServerReadyEvent*)e;

        Polygon polygon(server_ready_event->get_servers());
        voronoi_diagram_ = new VoronoiDiagram(polygon);

        BackgroundReadyEvent* background_ready_event = new BackgroundReadyEvent(voronoi_diagram_);
        event_manager->publish(EventType::BACKGROUND_READY, background_ready_event);
    };

    event_manager->subscribe(EventType::SERVER_READY, server_ready);
}