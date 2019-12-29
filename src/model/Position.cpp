//
// Created by abou on 19/12/2019.
//

#include "Position.hpp"

int Position::get_x() const
{
    return x_;
}

int Position::get_y() const
{
    return y_;
}

void Position::set_x(int x)
{
    x_ = x;
}

void Position::set_y(int y)
{
    Position::y_ = y;
}

Position::Position(int x, int y) : x_(x), y_(y)
{
    //initialise another things
}

Position Position::operator=(const Vector2D &item)
{
    return Position(item.x_, item.y_);
}
