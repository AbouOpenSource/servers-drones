//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#include "Controller.hpp"
#include "../core/service/ServiceContainer.hpp"

Controller::Controller(std::string& name): ServiceProvider(name)
{
    event_manager_ = (EventManager *) get_service(EventManager::SERVICE);
}

ServiceProvider *Controller::get_service(const std::string &service_id)
{
    return ServiceContainer::get_instance()->get_service(service_id);
}
