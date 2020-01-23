//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "AddServerAtPositionEvent.hpp"

AddServerAtPositionEvent::AddServerAtPositionEvent(InputManager::MousePosition position)
    : Event("Add Server At Position"),
    position_(position)
{}
