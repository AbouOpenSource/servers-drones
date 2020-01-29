//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_ADDSERVEREVENT_HPP
#define DRONEPROJECT_ADDSERVEREVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Server.hpp"


class AddServerEvent: public Event
{

public:

    explicit AddServerEvent(Server* server);

    Server *get_server() const;

    friend std::ostream &operator<<(std::ostream &os, const AddServerEvent &event);

private:

    Server* server_;

};


#endif //DRONEPROJECT_ADDSERVEREVENT_HPP
