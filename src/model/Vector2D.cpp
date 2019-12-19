#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-narrowing-conversions"
//
// Created by abou on 19/12/2019.
//

#include "Vector2D.hpp"
#include <cmath>
#include <algorithm>

int Vector2D::getAxisX() const
{
    return x_;
}

int Vector2D::getAxisY() const
{
    return y_;
}

void Vector2D::setAxisX(int x)
{
    x_ = x;
}

void Vector2D::setAxisY(int y)
{
    y_ = y;
}

Vector2D::Vector2D(int x, int y) : x_(x), y_(y)
{
    //make initialisation
}

float Vector2D::operator*(const Vector2D &op2) const
{
    return Vector2D::x_*op2.x_+Vector2D::y_*op2.y_;
}

void Vector2D::set(float x, float y)
{
        x_=x;
        y_=y;
}

Vector2D Vector2D::operator+(const Vector2D &op2) const
{
    return {Vector2D::x_+op2.x_, Vector2D::y_+op2.y_};
}

void Vector2D::normalize()
{
    float norm=sqrt(x_*x_+y_*y_);
    x_/=norm;
    y_/=norm;
}

Vector2D Vector2D::operator-(const Vector2D &op2) const
{

        return {Vector2D::x_ - op2.x_, Vector2D::y_ - op2.y_};

}

Vector2D::Vector2D(const Vector2D &)
{

}

Vector2D::~Vector2D()
{

}

Vector2D Vector2D::operator=(const Vector2D & item)
{
    return Vector2D(item.x_,item.y_);
}

Vector2D const Vector2D::operator/(int divisor) const
{
    return Vector2D(Vector2D::x_/divisor,Vector2D::y_/divisor);
}

Vector2D::Vector2D(Vector2D *copy)
{
            Vector2D::x_=copy->x_;
            Vector2D::y_=copy->y_;
}

#pragma clang diagnostic pop