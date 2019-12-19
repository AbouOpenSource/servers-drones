//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_VECTOR2D_HPP
#define DRONEPROJECT_VECTOR2D_HPP


class Vector2D {
private:
    int x_;
    int y_;
public:
    Vector2D(int x, int y);

    Vector2D (const Vector2D&);

    ~Vector2D();



    int getAxisX() const;

    int getAxisY() const;

    void setAxisX(int x);

    void setAxisY(int y);

    void set(float p_x,float p_y) ;

    void normalize() ;

    Vector2D operator-(const Vector2D &op2) const;

    Vector2D operator+(const Vector2D &op2) const;

    float operator*(const Vector2D &op2) const;

    Vector2D const operator/(int divisor) const;

    Vector2D operator=(const Vector2D&);

    Vector2D(Vector2D *p_d);
};

#endif //DRONEPROJECT_VECTOR2D_HPP
