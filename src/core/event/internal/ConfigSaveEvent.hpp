//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_CONFIGSAVEEVENT_HPP
#define DRONEPROJECT_CONFIGSAVEEVENT_HPP


#include <ostream>
#include "../Event.hpp"

class ConfigSaveEvent: public Event
{

public:

    ConfigSaveEvent();

    friend std::ostream &operator<<(std::ostream &os, const ConfigSaveEvent &event);

};


#endif //DRONEPROJECT_CONFIGSAVEEVENT_HPP
