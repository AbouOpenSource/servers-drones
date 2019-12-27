//
// Created by abou on 21/12/2019.
//

#ifndef DRONEPROJECT_CIRCLE_HPP
#define DRONEPROJECT_CIRCLE_HPP


#include "Position.hpp"
#include <math.h>
class Circle
{
private:
            Position center_;
            float raduis_;
public:

    Circle(const Position &center, float raduis) ;

    const Position &get_center() const;

    float get_raduis() const;

    void set_center(const Position &center);

    void set_raduis(float raduis);

    float area();

    float distance_with_other(Circle item);

    bool touch_with_other(Circle item);
};


#endif //DRONEPROJECT_CIRCLE_HPP
