//
// Created by Maanrifa Bacar Ali on 21/01/2020.
//

#ifndef DRONEPROJECT_EVENT_HPP
#define DRONEPROJECT_EVENT_HPP


#include <string>

class Event
{

protected:

    Event(const std::string& name);

public:
    const std::string &get_name() const;

private:

    std::string name_;

};


#endif //DRONEPROJECT_EVENT_HPP
