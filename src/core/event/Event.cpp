//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#include "Event.hpp"

Event::Event(const std::string &name): name_(name)
{}

const std::string &Event::get_name() const
{
    return name_;
}
