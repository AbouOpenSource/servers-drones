//
// Created by abou on 21/12/2019.
//

#ifndef DRONEPROJECT_CIRCLE_HPP
#define DRONEPROJECT_CIRCLE_HPP


#include "Position.hpp"
#include <math.h>

class Circle
{
public:

    Circle(const Position &center, float radius);

    const Position &get_center() const;

    float get_radius() const;

    void set_center(const Position &center);

    void set_radius(float raduis);

    float area();

    float distance_from(Circle* item);

    bool touch_with(Circle* item);

private:

    Position center_;

    float radius;
};


#endif //DRONEPROJECT_CIRCLE_HPP
