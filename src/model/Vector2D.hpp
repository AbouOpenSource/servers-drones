//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_VECTOR2D_HPP
#define DRONEPROJECT_VECTOR2D_HPP

#include <ostream>

class Vector2D
{

public :
    float x_, y_;

    Vector2D();

    Vector2D(const Vector2D &v);

    Vector2D(float p_x, float p_y);

    Vector2D operator-(const Vector2D &op2) const;

    Vector2D operator+(const Vector2D &op2) const;

    float operator*(const Vector2D &op2) const;

    friend Vector2D operator*(float a, const Vector2D &v);

    friend Vector2D operator / ( const Vector2D &v,float divisor);

    static Vector2D center(const Vector2D& point1, const Vector2D& point2);

    void set(float p_x,float p_y);

    void normalize();

    bool is_null();

    double norm();

    /********** Operator overload **********/
    friend std::ostream &operator<<(std::ostream &out, const Vector2D &vector);

    friend bool operator==(const Vector2D& vector1, const Vector2D& vector2);

    friend bool operator!=(const Vector2D& vector1, const Vector2D& vector2);

    Vector2D ortho();
};















#endif //DRONEPROJECT_VECTOR2D_HPP
