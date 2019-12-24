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

    const Position &getCenter() const;

    float getRaduis() const;

    void setCenter(const Position &center);

    void setRaduis(float raduis);

    float area();

    float distanceWithOther(Circle item);

    bool touchWithOther(Circle item);
};


#endif //DRONEPROJECT_CIRCLE_HPP
