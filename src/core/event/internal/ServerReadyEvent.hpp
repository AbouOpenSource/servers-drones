//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_SERVERREADYEVENT_HPP
#define DRONEPROJECT_SERVERREADYEVENT_HPP


#include "../Event.hpp"
#include "../../../model/Server.hpp"

class ServerReadyEvent: public Event
{

public:

    explicit ServerReadyEvent(std::vector<Server*>& servers);

    vector<Server *> &get_servers() const;

private:

    std::vector<Server*>& servers_;
};


#endif //DRONEPROJECT_SERVERREADYEVENT_HPP
