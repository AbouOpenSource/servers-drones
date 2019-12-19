//
// Created by abou on 19/12/2019.
//

#include "Position.hpp"

int Position::getX() const
{
    return x_;
}

int Position::getY() const
{
    return y_;
}

void Position::setX(int x)
{
    x_ = x;
}

void Position::setY(int y)
{
    Position::y_ = y;
}

Position::Position(int x, int y) : x_(x), y_(y)
{
    //initialise another things
}
