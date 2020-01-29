//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include <iostream>
#include "EventManager.hpp"
#include "internal/EventType.hpp"

std::string EventManager::SERVICE = "EventService";

EventManager::EventManager()
    : ServiceProvider(EventManager::SERVICE),
      subscriptions_({})
{}

void EventManager::publish(const char* event_type, Event *event)
{
    auto& subscriptions = get_subscriptions_for(event_type);

    /*if (event_type != EventType::FRAME_UPDATED && event_type != EventType::INPUT) {
        std::cout << "Called by: " << event_type << std::endl;
    }*/

    int i(0);
    for (auto& subscription: subscriptions) {
        subscription(event, {event_type, [&subscriptions, i] () {
            subscriptions.erase(subscriptions.begin() + i);
        }});
        i++;
    }
}

void EventManager::subscribe(const char* event_type, const Subscription& subscription)
{
    auto& subscriptions = get_subscriptions_for(event_type);
    subscriptions.push_back(subscription);
}

void EventManager::subscribe(const std::vector<const char *>& event_types, const EventManager::Subscription& subscription)
{
    for (auto& event_type: event_types) {
        subscribe(event_type, subscription);
    }
}

std::vector<EventManager::Subscription>& EventManager::get_subscriptions_for(const char* event_type)
{
    if (subscriptions_.find(event_type) == subscriptions_.end()) {
        subscriptions_[event_type] = std::vector<Subscription>();
    }
    return subscriptions_[event_type];
}
