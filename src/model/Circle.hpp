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
    /**
     * @brief the constructor of the circle
     * @param center: that is the coordinates of the center of circle.
     * @param radius: that is the radius of the circle.
     */
    Circle(const Position &center, float radius);
    /**
     * @brief getter of the circle
     * @return the center of the circle
     */
    const Position &get_center() const;
    /**
     * @brief getter of the radius
     * @return the radius of the circle
     */
    float get_radius() const;

    /**
     * @brief setter of the center of circle
     * @param center: center of the circle
     */
    void set_center(const Position &center);
    /**
     * @brief setter of the radius of circle
     * @param raduis: radius to affect
     */
    void set_radius(float raduis);
    /**
     * @brief computing of the area of the circle.
     * @return the area of the circle.
     */
    float area();
    /**
     * @brief Computing of the distance
     * @param item: other circle with this one we want to compute the distance
     * @return: the distance between two circles
     */
    float distance_from(Circle* item);
    /**
     * @brief check if two circles touch.
     * @param item
     * @return: true or false.
     */
    bool touch_with(Circle* item);

private:
    Position center_;

    float radius;
    /********** overriding of the output operator ************/
    friend std::ostream &operator<<(std::ostream &out, const Circle &circle);

};


#endif //DRONEPROJECT_CIRCLE_HPP
