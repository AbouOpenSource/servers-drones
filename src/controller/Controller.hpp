//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#ifndef DRONEPROJECT_CONTROLLER_HPP
#define DRONEPROJECT_CONTROLLER_HPP


#include "../core/event/EventManager.hpp"
#include "../core/service/ServiceContainer.hpp"

class Controller: public ServiceProvider
{

protected:

    explicit Controller(std::string& name);

    Controller(std::string& name, const std::vector<const char*>& managed_events);

    static ServiceProvider* get_service(const std::string& service_id);

    EventManager* event_manager_;

    void on_event(const char* event_type, Event* event);

};


#endif //DRONEPROJECT_CONTROLLER_HPP
