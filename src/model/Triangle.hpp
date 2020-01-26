#ifndef DRONEPROJECT_TRIANGLE_HPP
#define DRONEPROJECT_TRIANGLE_HPP

#include <vector>

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "determinant.hpp"
#include "../util/TypeUtil.hpp"

const float BLACK[4] = {0.0, 0.0, 0.0, 1.0f};
const float GREY[4] = {0.75f, 0.75f, 0.75f, 1.0f};
const float RED[4] = {1.0f, 0.0, 0.0, 1.0f};
const float ORANGE[4] = {1.0f, 0.27f, 0.0, 1.0f};
const float YELLOW[4] = {1.0f, 1.0f, 0.0, 1.0f};
const float GREEN[4] = {0.0, 1.0f, 0.0, 1.0f};
const float BLUE[4] = {0.0, 0.0, 1.0f, 1.0f};
const float PINK[4] = {0.9569f, 0.7529f, 0.7961f, 1.0f};
const float CYAN[4] = {0.0, 1.0f, 1.0f, 1.0f};

class Triangle
{

public:

    Vector2D *ptr_[3];
    bool is_highlighted_;
    Vector2D circum_center_;
    float circum_radius_;
    bool is_delaunay_;

    typedef std::function<void(Vector2D* point, unsigned int index)> PointCallback;

    Triangle();

    Triangle(Triangle* toCopy);

    Triangle(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    //bool is_equilateral() {
    //  return true;
    //}

    bool is_empty();

    void update_vertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    void calculate_circle();

    void on_mouse_move(const Vector2D& pos);

    bool is_on_the_left(const Vector2D *P, const Vector2D *P1, const Vector2D *P2);

    bool is_empty(const std::vector<Vector2D*> &tmp, int n);

    bool is_inside(const Vector2D &p);

    bool is_inside_circle(const Vector2D &p);

    bool check_delaunay(const std::vector<Vector2D> &points);

    void draw();

    void draw_circle();

    bool common_point(Vector2D* point);

    void foreach_point(PointCallback cb);

    /********** Operator overloading **********/
    friend bool operator==(Triangle& triangle1, Triangle& triangle2);

    friend std::ostream &operator<<(std::ostream &out, Triangle &triangle);
};

#endif //DRONEPROJECT_TRIANGLE_HPP

