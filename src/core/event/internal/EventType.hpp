//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_EVENTTYPE_HPP
#define DRONEPROJECT_EVENTTYPE_HPP


#include <string>

class EventType
{

public:

    static std::string CHANGE_SERVER_COLOR;
    static std::string CLEAR_SELECTION;
    static std::string DELETE_SELECTED_SERVER;
    static std::string CHANGE_SELECTED_SERVERS_COLOR;
    static std::string ADD_SERVER_TO_POSITION;
    static std::string ADD_SERVER_TO_BEGIN;
    static std::string SAVE_CONFIG_STATE;
    static std::string FRAME_UPDATE;
    static std::string SERVER_READY;
};


#endif //DRONEPROJECT_EVENTTYPE_HPP
