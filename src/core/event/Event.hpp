//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_EVENT_HPP
#define DRONEPROJECT_EVENT_HPP


#include <string>

class Event
{

protected:

    Event();

public:

    friend std::ostream& operator<<(std::ostream& os, const Event& e);

};


#endif //DRONEPROJECT_EVENT_HPP
