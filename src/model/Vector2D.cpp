#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by abou on 19/12/2019.
//

#include "Vector2D.hpp"
#include <cmath>
#include <algorithm>

Vector2D::Vector2D()
        : x_(0),
          y_(0)
{
}

Vector2D::Vector2D(const Vector2D &v)
{
    x_ = v.x_;
    y_ = v.y_;
}

Vector2D::Vector2D(float p_x, float p_y)
        : x_(p_x),
          y_(p_y)
{
}

void Vector2D::set(float p_x,float p_y)
{
    x_=p_x;
    y_=p_y;
}

void Vector2D::normalize()
{
    float norm= std::sqrt(x_*x_+y_*y_);

    x_ /= norm;
    y_ /= norm;
}

double Vector2D::norm()
{
    return std::sqrt(x_ * x_ + y_ * y_);
}

Vector2D Vector2D::ortho()
{
    return Vector2D(-y_,x_);
}

Vector2D Vector2D::center(const Vector2D &vertex1, const Vector2D &vertex2)
{
    return (vertex1 + vertex2) / 2;
}

//Vector2D Vector2D::center(const Vector2D &vector)
//{
//    return Vector2D();
//}

Vector2D Vector2D::operator-(const Vector2D &op2) const
{
    return Vector2D(x_ - op2.x_, y_ - op2.y_);
}

Vector2D Vector2D::operator+(const Vector2D &op2) const
{
    return Vector2D(x_ + op2.x_, y_ + op2.y_);
}

float Vector2D::operator*(const Vector2D &op2) const
{
    return x_*op2.x_+y_*op2.y_;
}

Vector2D operator*(float a, const Vector2D &v)
{
    return Vector2D(a * v.x_, a * v.y_);
}


 Vector2D operator/(const Vector2D &v, float divisor)
{
    return Vector2D(v.x_ / divisor,v.y_ / divisor);
}

std::ostream &operator<<(std::ostream &out, Vector2D &vector)
{
    out << "Vector2D | x: " << vector.x_ << ", y: " << vector.y_;
    return out;
}

bool operator==(const Vector2D &vector1, const Vector2D &vector2)
{
    return vector1.x_ == vector2.x_ && vector1.y_ == vector2.y_;
}

#pragma clang diagnostic pop