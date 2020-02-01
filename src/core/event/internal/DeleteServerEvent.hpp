//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#ifndef DRONEPROJECT_DELETESERVEREVENT_HPP
#define DRONEPROJECT_DELETESERVEREVENT_HPP


#include "../Event.hpp"
#include "../../../model/Server.hpp"

class DeleteServerEvent: public Event
{

public:

    explicit DeleteServerEvent(Server* server);

    Server *get_server() const;

    friend std::ostream &operator<<(std::ostream &os, const DeleteServerEvent &event);

private:

    Server* server_;

};


#endif //DRONEPROJECT_DELETESERVEREVENT_HPP
