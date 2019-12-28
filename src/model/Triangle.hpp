#ifndef DRONEPROJECT_TRIANGLE_HPP
#define DRONEPROJECT_TRIANGLE_HPP

#include <vector>

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "determinant.hpp"

const float BLACK[4] = {0.0, 0.0, 0.0, 1.0f};
const float GREY[4] = {0.75f, 0.75f, 0.75f, 1.0f};
const float RED[4] = {1.0f, 0.0, 0.0, 1.0f};
const float ORANGE[4] = {1.0f, 0.27f, 0.0, 1.0f};
const float YELLOW[4] = {1.0f, 1.0f, 0.0, 1.0f};
const float GREEN[4] = {0.0, 1.0f, 0.0, 1.0f};
const float BLUE[4] = {0.0, 0.0, 1.0f, 1.0f};

class Triangle {
public:
    Vector2D *ptr[3];
    bool is_highlighted_;
    Vector2D circum_center_;
    float circum_radius_;
    bool is_delaunay_;

    Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3);

//    bool is_equilateral() {
//        return true;
//    }

    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3);

    void calculateCircle();

    void onMouseMove(const Vector2D& pos);

    bool is_on_the_left(const Vector2D *P, const Vector2D *P1, const Vector2D *P2);

    bool isEmpty(const std::vector<Vector2D*> &tmp,int n);

    bool is_inside(const Vector2D &P);

    bool is_inside_circle(const Vector2D &P);

    bool check_delaunay(const std::vector<Vector2D> &points);

    void draw();

    void drawCircle();
};

#endif //DRONEPROJECT_TRIANGLE_HPP

