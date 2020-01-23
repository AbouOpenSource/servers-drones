//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "ClearSelectionEvent.hpp"

ClearSelectionEvent::ClearSelectionEvent(std::vector<Server*> servers)
    : Event("Clear Selection"),
    servers_(servers)
{}
