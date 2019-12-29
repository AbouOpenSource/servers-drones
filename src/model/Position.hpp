//
// Created by abou on 19/12/2019.
//

#ifndef DRONEPROJECT_POSITION_HPP
#define DRONEPROJECT_POSITION_HPP


#include "Vector2D.hpp"

class Position {
private :
    int x_;
    int y_;


public:
    int get_x() const;

    int get_y() const;

    void set_x(int x);

    void set_y(int y);

    Position(int x, int y);

    Position operator=(const Vector2D& item);
};


#endif //DRONEPROJECT_POSITION_HPP
