//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#include "FrameUpdateEvent.hpp"

FrameUpdateEvent::FrameUpdateEvent(Window *window)
    : Event(),
      window_(window)
{}

std::ostream &operator<<(std::ostream &os, const FrameUpdateEvent &event)
{
    os << "Frame will update" << std::endl;
    return os;
}

