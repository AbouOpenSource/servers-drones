//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "SelectionClearEvent.hpp"

SelectionClearEvent::SelectionClearEvent(std::vector<Server*>& servers)
    : Event(),
    servers_(servers)
{}

std::vector<Server *> &SelectionClearEvent::get_servers() const
{
    return servers_;
}

std::ostream &operator<<(std::ostream &os, const SelectionClearEvent &event)
{
    os << "Selection cleared" << std::endl;
    return os;
}
