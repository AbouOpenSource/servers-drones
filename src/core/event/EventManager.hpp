//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_EVENTMANAGER_HPP
#define DRONEPROJECT_EVENTMANAGER_HPP


#include <map>
#include <vector>
#include <functional>
#include "Event.hpp"
#include "../service/ServiceProvider.hpp"

class EventManager: public ServiceProvider
{

public:

    static std::string SERVICE;

    typedef std::function<void(Event*)> Subscription;

    EventManager();

    void publish(const std::string& event_type, Event* event);

    void subscribe(const std::string& event_type, Subscription&);

private:

    std::vector<Subscription> get_subscriptions_for(const std::string& event_type);

    std::map<std::string, std::vector<Subscription>> subscriptions_;

};


#endif //DRONEPROJECT_EVENTMANAGER_HPP
