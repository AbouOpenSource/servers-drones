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
/**
 * @brief: EventManager that class manages all of the events of the system
 * @details This class captures all of the event to system. That allows to manges very easily a lot of problem.
 */
class EventManager: public ServiceProvider
{

public:
    /**
     * allows to identifier this service in the app.
     * @details
     */
    static std::string SERVICE;
    /**
     * @details each event that is launched have some details.
     * The EventDetail class contents the callback to call if the event is occured
     */
    struct EventDetail {
        const char* type;
        const TypeUtil::Callback& unsubscribe;
    };
    /**
     * callback for the subscription event.
     */
    typedef std::function<void(Event* e, const EventDetail& detail)> Subscription;
    /**
     * @brief: default constructor of the class
     */
    EventManager();
    /**
     * @brief publish like send the messages to all of subcripbers of this kind of the event.
     * @param event_type
     * @param event
     */
    void publish(const char* event_type, Event* event);
    /**
     * @brief function to susbcribe to the topic
     * @param event_type
     */
    void subscribe(const char* event_type, const Subscription&);
    /**
     *@brief susbcribe function
     * @param event_types
     */
    void subscribe(const std::vector<const char*>& event_types, const Subscription&);

private:

    std::vector<Subscription>& get_subscriptions_for(const char* event_type);

    std::map<const char*, std::vector<Subscription>> subscriptions_;

};


#endif //DRONEPROJECT_EVENTMANAGER_HPP
