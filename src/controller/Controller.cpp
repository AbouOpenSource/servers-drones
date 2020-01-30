//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#include "Controller.hpp"
#include "../core/service/ServiceContainer.hpp"

Controller::Controller(std::string& name)
    : ServiceProvider(name),
    event_manager_((EventManager *) get_service(EventManager::SERVICE))
{}

Controller::Controller(std::string &name, const std::vector<const char *> &managed_events)
    : ServiceProvider(name),
    event_manager_((EventManager *) get_service(EventManager::SERVICE))
{
    /*for (auto& event_type: managed_events) {
        event_manager_->subscribe(event_type, [this] (Event* event, const EventManager::EventDetail& detail) {
            on_event(detail.type, event);
        });
    }*/
}

ServiceProvider *Controller::get_service(const std::string &service_id)
{
    return ServiceContainer::get_instance()->get_service(service_id);
}

void Controller::on_event(const char *event_type, Event *event)
{}
