//
// Created by abou on 21/12/2019.
//

#include "Circle.hpp"

Circle::Circle(const Position &center, float radius) : center_(center), radius(radius)
{}

const Position &Circle::get_center() const
{
    return center_;
}

float Circle::get_radius() const
{
    return radius;
}

void Circle::set_center(const Position &center)
{
    center_ = center;
}

void Circle::set_radius(float raduis)
{
    radius = raduis;
}

float Circle::area()
{
    return get_radius() * Circle::get_radius() * M_PI;
}

float Circle::distance_from(Circle *item)
{

    return sqrt(
            center_.get_x() - item->center_.get_x() * center_.get_x() - item->center_.get_x() +
            center_.get_y() - item->center_.get_y() * center_.get_y() - item->center_.get_y()
    );
}

bool Circle::touch_from(Circle *item)
{
    return distance_from(item) < item->get_radius() + get_radius();
}


