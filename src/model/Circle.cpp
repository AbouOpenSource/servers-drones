//
// Created by abou on 21/12/2019.
//

#include "Circle.hpp"

Circle::Circle(const Position &center, float raduis) : center_(center), raduis_(raduis)
{

}

const Position &Circle::get_center() const
{
    return center_;
}

float Circle::get_raduis() const
{
    return raduis_;
}

void Circle::set_center(const Position &center)
{
    center_ = center;
}

void Circle::set_raduis(float raduis)
{
    raduis_ = raduis;
}

float Circle::area()
{
    return Circle::get_raduis()*Circle::get_raduis()*M_PI;
}

float Circle::distance_with_other(Circle item)
{

   return sqrt(
           center_.get_x() - item.center_.get_x() * center_.get_x() - item.center_.get_x() +
                   center_.get_y() - item.center_.get_y() * center_.get_y() - item.center_.get_y()
            );
}

bool Circle::touch_with_other(Circle item)
{
    return Circle::distance_with_other(item) < item.get_raduis() + Circle::get_raduis();
}


