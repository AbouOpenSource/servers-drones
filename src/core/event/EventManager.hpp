//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_EVENTMANAGER_HPP
#define DRONEPROJECT_EVENTMANAGER_HPP


#include <map>
#include <vector>
#include "Event.hpp"
#include "../service/ServiceProvider.hpp"
#include "../../util/TypeUtil.hpp"

class EventManager: public ServiceProvider
{

public:

    static std::string SERVICE;

    struct EventDetail {
        const char* type;
        const TypeUtil::Callback& unsubscribe;
    };

    typedef std::function<void(Event* e, const EventDetail& detail)> Subscription;

    EventManager();

    void publish(const char* event_type, Event* event);

    void subscribe(const char* event_type, const Subscription&);

    void subscribe(const std::vector<const char*>& event_types, const Subscription&);

private:

    std::vector<Subscription>& get_subscriptions_for(const char* event_type);

    std::map<const char*, std::vector<Subscription>> subscriptions_;

};


#endif //DRONEPROJECT_EVENTMANAGER_HPP
