//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_EVENTMANAGER_HPP
#define DRONEPROJECT_EVENTMANAGER_HPP


#include <map>
#include "../ServiceProvider.hpp"
#include "Event.hpp"

class EventManager: ServiceProvider
{

public:

    static std::string SERVICE;

    EventManager();

    void publish(const std::string& event_type, Event* event);

    void subscribe(const std::string& event_type);

private:

    void ensure_subscription_exists();

    //std::map<std::string, std::call> subsciptions_;

};


#endif //DRONEPROJECT_EVENTMANAGER_HPP
