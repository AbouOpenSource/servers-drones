#ifndef DRONEPROJECT_TRIANGLE_HPP
#define DRONEPROJECT_TRIANGLE_HPP

#include <vector>

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "../util/TypeUtil.hpp"
#include "../view/View.hpp"
#include "Determinant.hpp"

class Triangle
{

public:

    Vector2D *ptr_[3];
    /**
     * @brief callback on each point of the triangle.
     */
    typedef std::function<void(Vector2D* point, unsigned int index)> PointCallback;

    /********** Constructor & destructor **********/
    Triangle();
    /**
     * @brief costructor of copy
     * @param toCopy
     */
    Triangle(Triangle* toCopy);
    /**
     * @brief constructor of initialization
     * @param ptr1 first point of the triangle
     * @param ptr2 second point of the triangle
     * @param ptr3
     */
    Triangle(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    /********** Capacity **********/
    bool is_empty();

    /********** Getter **********/
    float get_circum_radius() const;

    bool is_highlighted() const;

    bool is_delaunay() const;

    const Vector2D &get_circum_center() const;

    /********** Modifiers **********/
    void calculate_circle();

    bool check_delaunay(const std::vector<Vector2D> &points);

    /********** Others **********/
    void update_vertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    void on_mouse_move(const Vector2D& pos);

    bool is_on_the_left(const Vector2D *P, const Vector2D *P1, const Vector2D *P2);

    bool is_empty(const std::vector<Vector2D*> &tmp, int n);

    bool is_inside(const Vector2D &p);

    bool is_inside_circle(const Vector2D &p);

    void draw();

    void draw_circle();

    bool common_point(Vector2D* point);

    void foreach_point(PointCallback cb);

    /********** Operator overloading **********/
    friend bool operator==(Triangle& triangle1, Triangle& triangle2);

    friend std::ostream &operator<<(std::ostream &out, Triangle &triangle);

private:
    bool is_highlighted_;

    Vector2D circum_center_;

    float circum_radius_;

    bool is_delaunay_;
};

#endif //DRONEPROJECT_TRIANGLE_HPP