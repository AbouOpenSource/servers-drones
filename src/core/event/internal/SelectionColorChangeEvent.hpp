//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_SELECTIONCOLORCHANGEEVENT_HPP
#define DRONEPROJECT_SELECTIONCOLORCHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/Server.hpp"

class SelectionColorChangeEvent: public Event
{

public:

    SelectionColorChangeEvent(std::vector<Server*>& servers, const std::string& color);

    std::string get_color() const;

    std::vector<Server *> &get_servers() const;

    friend std::ostream &operator<<(std::ostream &os, const SelectionColorChangeEvent &event);

private:

    std::string color_;

    std::vector<Server*>& servers_;

};


#endif //DRONEPROJECT_SELECTIONCOLORCHANGEEVENT_HPP
