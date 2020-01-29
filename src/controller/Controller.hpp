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

    Controller(std::string& name);

    static ServiceProvider* get_service(const std::string& service_id);

    EventManager* event_manager_;

};


#endif //DRONEPROJECT_CONTROLLER_HPP
