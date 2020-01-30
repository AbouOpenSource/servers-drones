//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_POSITION_HPP
#define DRONEPROJECT_POSITION_HPP


#include "Vector2D.hpp"

class Position {

public:
    /**
     * @brief: the constructor of the position
     * @param x : axis x of the position.
     * @param y : axis y of the position.
     */
    Position(int x, int y);
    /**
     * @brief getter of X
     * @return int;
     */
    int get_x() const;
    /**
     * @brief: getter Y
     * @return int;
     */
    int get_y() const;
    /**
     * @brief : setter of X
     * @param x : axis x
     */
    void set_x(int x);
    /**
     * @brief : setter of y
     * @param y : axis y
     */
    void set_y(int y);
    /**
     * @param item if we consider vector like a position
     * @return true if positon.x==vector.x and position.y==vectoe.y
     */
    Position operator=(const Vector2D& item);

private :

    int x_;
    int y_;
};


#endif //DRONEPROJECT_POSITION_HPP
