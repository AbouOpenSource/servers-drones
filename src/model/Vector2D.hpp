//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_VECTOR2D_HPP
#define DRONEPROJECT_VECTOR2D_HPP


class Vector2D {

public:

    int x_;
    int y_;

    Vector2D();

    Vector2D(int x, int y);

    Vector2D (const Vector2D& test);

    void set(float p_x,float p_y);

    void normalize();

    double norm();

    Vector2D ortho();

    Vector2D operator-(const Vector2D &op2) const;

    Vector2D operator+(const Vector2D &op2) const;

    float operator*(const Vector2D &op2) const;

    Vector2D const operator/(int divisor) const;

    Vector2D operator *(int divisor) const;

    Vector2D operator=(const Vector2D&);

    Vector2D(Vector2D *p_d);

    bool operator == (const Vector2D& item);

    friend Vector2D operator*(float a,const Vector2D &v);
};

#endif //DRONEPROJECT_VECTOR2D_HPP
