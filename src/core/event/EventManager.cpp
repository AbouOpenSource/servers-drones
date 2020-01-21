//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "EventManager.hpp"

std::string EventManager::SERVICE = "EventService";

EventManager::EventManager(): ServiceProvider(EventManager::SERVICE)//, subsciptions_(std::vector<Event*>())
{

}

void EventManager::publish(const std::string &event_type, Event *event)
{

}

void EventManager::subscribe(const std::string &event_type)
{

}
