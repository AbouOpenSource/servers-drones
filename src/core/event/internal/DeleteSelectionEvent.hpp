//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_DELETESELECTIONEVENT_HPP
#define DRONEPROJECT_DELETESELECTIONEVENT_HPP


#include "../../../model/Server.hpp"
#include "../Event.hpp"
#include <vector>

class DeleteSelectionEvent: public Event
{

public:

    explicit DeleteSelectionEvent(std::vector<Server*> servers);

private:

    std::vector<Server*> servers_;

};


#endif //DRONEPROJECT_DELETESELECTIONEVENT_HPP
