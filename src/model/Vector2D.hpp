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
    /**
     * @brief default constructor of the class
     */
    Vector2D();
    /**
     * @brief : constructor of copy of the class Vector2D
     * @param v item to copy
     */
    Vector2D(const Vector2D &v);
    /**
     * @brief cnstructor of creating
     * @param p_x: parameter for the x coordinates
     * @param p_y: parameter for the y coordinates
     */
    Vector2D(float p_x, float p_y);
    /**
     * @brief overriding of the operator -
     * @param op2 the second element of the operators
     * @return return the resultant Vector
     */
    Vector2D operator-(const Vector2D &op2) const;
/**
     * @brief overriding of the operator +
     * @param op2 the second element of the operators
     * @return return the resultant Vector
     */

    Vector2D operator+(const Vector2D &op2) const;
/**
     * @brief overriding of the operator *
     * @param op2 the second element of the operators
     * @return return the resultant float
     */

    float operator*(const Vector2D &op2) const;
    /**
     * @brief multiple the vector by the float
     * @param a float to multiple
     * @param v Vector to
     * @return the vector resultant of the operation
     */
    friend Vector2D operator*(float a, const Vector2D &v);
/**
     * @brief the vector divides by a float
     * @param divisor divisor
     * @param v vector to divide
     * @return the vector resultant of the operation
     */

    friend Vector2D operator / ( const Vector2D &v,float divisor);

    static Vector2D center(const Vector2D& point1, const Vector2D& point2);

    void set(float p_x,float p_y);
    /**
     * @brief normalise the vector
     * @details allows to get the direction and the sens of the vector with th orm 1.
     */
    void normalize();
    /**
     * @brief : compute the norm of the vector
     * @return the norm of the vector
     */
    double norm();

    /********** Operator overload **********/
    friend std::ostream &operator<<(std::ostream &out, const Vector2D &vector);

    friend bool operator==(const Vector2D& vector1, const Vector2D& vector2);

    Vector2D ortho();
};















#endif //DRONEPROJECT_VECTOR2D_HPP
