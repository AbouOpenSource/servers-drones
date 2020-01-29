//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "SelectionDeleteEvent.hpp"

SelectionDeleteEvent::SelectionDeleteEvent(std::vector<Server*>& servers)
    : Event(),
    servers_(servers)
{}

std::vector<Server *> &SelectionDeleteEvent::get_servers() const
{
    return servers_;
}

ostream &operator<<(std::ostream &os, const SelectionDeleteEvent &event)
{
    os << "Selection deleted" << std::endl;
    return os;
}
