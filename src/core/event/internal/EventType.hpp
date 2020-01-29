//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_EVENTTYPE_HPP
#define DRONEPROJECT_EVENTTYPE_HPP


#include <string>

class EventType
{

public:

    static const char* SELECTION_CLEARED;
    static const char* SELECTION_DELETED;
    static const char* SELECTION_COLOR_CHANGED;

    static const char* DRONE_ADDED;
    static const char* SERVER_ADDED;

    static const char* CONFIG_SAVED;
    static const char* CONFIG_LOADED;

    static const char* SERVER_CONFIG_CHANGED;
    static const char* DRONE_CONFIG_CHANGED;

    static const char* COLLISION_DETECTED;

    static const char* FRAME_UPDATED;
    static const char* DIAGRAM_CHANGED;

    static const char* MOUSE_MOVED;
    static const char* MOUSE_CLICKED;
    static const char* KEY_PRESSED;
    static const char* INPUT;
};


#endif //DRONEPROJECT_EVENTTYPE_HPP
