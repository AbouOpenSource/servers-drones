//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "EventManager.hpp"

std::string EventManager::SERVICE = "EventService";

EventManager::EventManager()
    : ServiceProvider(EventManager::SERVICE),
      subscriptions_({})
{}

void EventManager::publish(const std::string &event_type, Event *event)
{
    auto subscriptions = get_subscriptions_for(event_type);
    for (const auto& subscription: subscriptions) {
        subscription(event);
    }
}

void EventManager::subscribe(const std::string &event_type, Subscription& subscription)
{
    auto subscriptions = get_subscriptions_for(event_type);
    subscriptions.push_back(subscription);
}

std::vector<EventManager::Subscription> EventManager::get_subscriptions_for(const std::string& event_type)
{
    if (subscriptions_.find(event_type) != subscriptions_.end()) {
        subscriptions_.insert({event_type, std::vector<Subscription>()});
    }
    return subscriptions_[event_type];
}
