//
// Created by Maanrifa Bacar Ali on 01/02/2020.
//

#include "DeleteServerEvent.hpp"

DeleteServerEvent::DeleteServerEvent(Server* server)
        : Event(),
          server_(server)
{}

Server *DeleteServerEvent::get_server() const
{
    return server_;
}

std::ostream &operator<<(std::ostream &os, const DeleteServerEvent &event)
{
    os << "Deleted server: " << event.server_ << std::endl;
    return os;
}
