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

    friend Vector2D operator*(const Vector2D &v, float a);


    friend Vector2D operator / ( const Vector2D &v,float divisor);

    void set(float p_x,float p_y);

    void normalize();

    double norm();

    /********** Operator overload **********/
    friend std::ostream &operator<<(std::ostream &out, const Vector2D &vector);

    Vector2D ortho();

    Vector2D unitaire();
};















#endif //DRONEPROJECT_VECTOR2D_HPP
