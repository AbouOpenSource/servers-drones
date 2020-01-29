//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "SelectionColorChangeEvent.hpp"

SelectionColorChangeEvent::SelectionColorChangeEvent(std::vector<Server*>& servers, const std::string &color)
    : Event(),
    servers_(servers),
    color_(color)
{}

std::string SelectionColorChangeEvent::get_color() const
{
    return color_;
}

std::vector<Server *> &SelectionColorChangeEvent::get_servers() const
{
    return servers_;
}


std::ostream &operator<<(std::ostream &os, const SelectionColorChangeEvent &event)
{
    os << "Selection color changed" << std::endl;
    return os;
}
