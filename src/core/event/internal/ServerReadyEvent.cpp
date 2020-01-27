//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "ServerReadyEvent.hpp"

ServerReadyEvent::ServerReadyEvent(std::vector<Server*> &servers)
    : Event("Servers are ready"),
      servers_(servers)
{}

vector<Server *> &ServerReadyEvent::get_servers() const
{
    return servers_;
}
