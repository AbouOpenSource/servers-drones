//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "DeleteSelectionEvent.hpp"

DeleteSelectionEvent::DeleteSelectionEvent(std::vector<Server*> servers)
        : Event("Delete Selection"),
          servers_(servers)
{}