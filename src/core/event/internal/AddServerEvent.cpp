//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "AddServerEvent.hpp"

AddServerEvent::AddServerEvent(Server* server)
    : Event(),
    server_(server)
{}

Server *AddServerEvent::get_server() const
{
    return server_;
}

std::ostream &operator<<(std::ostream &os, const AddServerEvent &event)
{
    os << "Added server: " << event.server_ << std::endl;
    return os;
}
