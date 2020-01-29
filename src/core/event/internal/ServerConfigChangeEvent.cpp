//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "ServerConfigChangeEvent.hpp"

ServerConfigChangeEvent::ServerConfigChangeEvent(std::vector<Server*> &servers)
    : Event(),
      servers_(servers)
{}

std::vector<Server *> &ServerConfigChangeEvent::get_servers() const
{
    return servers_;
}

std::ostream &operator<<(std::ostream &os, const ServerConfigChangeEvent &event)
{
    os << "Server configuration changed" << std::endl;
    return os;
}
