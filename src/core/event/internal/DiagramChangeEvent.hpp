//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#ifndef DRONEPROJECT_DIAGRAMCHANGEEVENT_HPP
#define DRONEPROJECT_DIAGRAMCHANGEEVENT_HPP


#include <ostream>
#include "../Event.hpp"
#include "../../../model/MyPolygon.hpp"
#include "../../../controller/DiagramController.hpp"

class DiagramChangeEvent: public Event
{

public:

    DiagramChangeEvent(DiagramController* diagram_controller);

    DiagramController *get_diagram_controller() const;

    friend std::ostream &operator<<(std::ostream &os, const DiagramChangeEvent &event);

private:

    DiagramController* diagram_controller_;

};


#endif //DRONEPROJECT_DIAGRAMCHANGEEVENT_HPP
