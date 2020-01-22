//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_CLEARSELECTIONEVENT_HPP
#define DRONEPROJECT_CLEARSELECTIONEVENT_HPP


#include "../Event.hpp"
#include "../../../model/Server.hpp"
#include <vector>

class ClearSelectionEvent: public Event
{

public:

    explicit ClearSelectionEvent(std::vector<Server*> servers);

private:

    std::vector<Server*> servers_;

};


#endif //DRONEPROJECT_CLEARSELECTIONEVENT_HPP
