#ifndef DRONEPROJECT_VECTOR2D_HPP
#define DRONEPROJECT_VECTOR2D_HPP

#include <cmath>

class Vector2D {
public :
    float x,y;
    Vector2D():x(0),y(0) {};
    Vector2D(const Vector2D &v) {x=v.x; y=v.y; }
    Vector2D(float p_x,float p_y):x(p_x),y(p_y) {};
    Vector2D operator-(const Vector2D &op2) const {
        return Vector2D(x - op2.x, y - op2.y);
    }
    Vector2D operator+(const Vector2D &op2) const {
        return Vector2D(x + op2.x, y + op2.y);
    }
    float operator*(const Vector2D &op2) const {
        return x*op2.x+y*op2.y;
    }
    void set(float p_x,float p_y) {
        x=p_x;
        y=p_y;
    }
    void normalize() {
        float norm= std::sqrt(x*x+y*y);
        x/=norm;
        y/=norm;
    }
    double norm() {
        return std::sqrt(x*x+y*y);
    }
    Vector2D ortho() {
        return Vector2D(-y,x);
    }
};

Vector2D operator*(float a,const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}

#endif //DRONEPROJECT_VECTOR2D_HPP
