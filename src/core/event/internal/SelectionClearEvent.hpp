//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_SELECTIONCLEAREVENT_HPP
#define DRONEPROJECT_SELECTIONCLEAREVENT_HPP


#include "../Event.hpp"
#include "../../../model/Server.hpp"
#include <vector>
#include <ostream>

class SelectionClearEvent: public Event
{

public:

    explicit SelectionClearEvent(std::vector<Server*>& servers);

    std::vector<Server *> &get_servers() const;

    friend std::ostream &operator<<(std::ostream &os, const SelectionClearEvent &event);

private:

    std::vector<Server*>& servers_;

};


#endif //DRONEPROJECT_SELECTIONCLEAREVENT_HPP
