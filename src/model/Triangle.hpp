#ifndef DRONEPROJECT_TRIANGLE_HPP
#define DRONEPROJECT_TRIANGLE_HPP

#include <vector>

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "determinant.hpp"

class Triangle {

public:

    Triangle(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    //bool is_equilateral() {
    //  return true;
    //}

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

    float get_circum_radius() const;

    bool is_highlighted() const;

    bool is_delaunay() const;

    const Vector2D &get_circum_center() const;

    Vector2D *ptr_[3];

private:

    float circum_radius_;

    bool is_highlighted_;
    bool is_delaunay_;
    Vector2D circum_center_;
};

#endif //DRONEPROJECT_TRIANGLE_HPP

