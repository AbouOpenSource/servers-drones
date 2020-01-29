//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_SERVERCONFIGCHANGEEVENT_HPP
#define DRONEPROJECT_SERVERCONFIGCHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Server.hpp"

class ServerConfigChangeEvent: public Event
{

public:

    explicit ServerConfigChangeEvent(std::vector<Server*>& servers);

    std::vector<Server*> &get_servers() const;

    friend std::ostream &operator<<(std::ostream &os, const ServerConfigChangeEvent &event);

private:

    std::vector<Server*>& servers_;
};


#endif //DRONEPROJECT_SERVERCONFIGCHANGEEVENT_HPP
