//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "DiagramChangeEvent.hpp"

DiagramChangeEvent::DiagramChangeEvent(DiagramController *diagram_controller)
    : Event(),
    diagram_controller_(diagram_controller)
{}

DiagramController *DiagramChangeEvent::get_diagram_controller() const
{
    return diagram_controller_;
}

ostream &operator<<(std::ostream &os, const DiagramChangeEvent &event)
{
    os << "Diagram scheme updated" << std::endl;
    return os;
}
