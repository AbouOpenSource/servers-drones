//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "ConfigSaveEvent.hpp"

ConfigSaveEvent::ConfigSaveEvent()
    : Event()
{}

std::ostream &operator<<(std::ostream &os, const ConfigSaveEvent &event)
{
    os << "Configuration saved" << std::endl;
    return os;
}
