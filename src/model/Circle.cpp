//
// Created by abou on 21/12/2019.
//

#include "Circle.hpp"

Circle::Circle(const Position &center, float raduis) : center_(center), raduis_(raduis)
{

}

const Position &Circle::getCenter() const
{
    return center_;
}

float Circle::getRaduis() const
{
    return raduis_;
}

void Circle::setCenter(const Position &center)
{
    center_ = center;
}

void Circle::setRaduis(float raduis)
{
    raduis_ = raduis;
}

float Circle::area()
{
    return Circle::getRaduis()*Circle::getRaduis()*M_1_PI;
}

float Circle::distanceWithOther(Circle item)
{

   return sqrt(
            center_.getX()-item.center_.getX()*center_.getX()-item.center_.getX()   +
               center_.getY()-item.center_.getY() *center_.getY()- item.center_.getY()
            );
}

bool Circle::touchWithOther(Circle item)
{
    return Circle::distanceWithOther(item) < item.getRaduis() + Circle::getRaduis();
}


