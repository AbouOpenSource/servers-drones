//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_SELECTIONDELETEEVENT_HPP
#define DRONEPROJECT_SELECTIONDELETEEVENT_HPP


#include "../../../model/Server.hpp"
#include "../Event.hpp"
#include <vector>
#include <ostream>

class SelectionDeleteEvent: public Event
{

public:

    explicit SelectionDeleteEvent(std::vector<Server*>& servers);

    std::vector<Server *> &get_servers() const;

    friend std::ostream &operator<<(std::ostream &os, const SelectionDeleteEvent &event);

private:

    std::vector<Server*>& servers_;

};


#endif //DRONEPROJECT_SELECTIONDELETEEVENT_HPP
