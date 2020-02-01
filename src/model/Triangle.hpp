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

    /**
     * @brief default constructor.
     */
    Triangle();

    /**
     * @brief constructor of copy.
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

    /********** Getter **********/

    /**
     * @brief getter for the circum_radius_ variable.
     * @return the circum_radius_ variable.
     */
    float get_circum_radius() const;

    /**
     * @brief getter for the is_highlighted variable.
     * @return the highlighted variable.
     */
    bool is_highlighted() const;

    /**
     * @brief getter for the is_delaunay variable.
     * @return the is_delaunay_ variable.
     */
    bool is_delaunay() const;

    /**
     * @brief getter for the circum_center_ variable.
     * @return the circum_center_ variable.
     */
    const Vector2D &get_circum_center() const;

    /********** Modifiers **********/

    /**
     * @brief calculate the circum_radius_ and circum_center_ of the triangle.
     */
    void calculate_circle();

    /**
     * @brief check if the triangle is delaunay.
     * @param points a list of point to check if they are inside the circumscribed circle of the triangle.
     * @return true if it is delaunay, false otherwise.
     */
    bool check_delaunay(const std::vector<Vector2D> &points);

    /********** Others **********/

    /**
     * @brief update the triangle with 3 news vertices.
     * @param ptr1 the first vertex.
     * @param ptr2 the second vertex.
     * @param ptr3 the third vertex.
     */
//    void update_vertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3);

    /**
     * @brief update the is_highlighted_ variable depending of the point passed in parameter.
     * @param pos the point to check if it inside the triangle.
     */
//    void on_mouse_move(const Vector2D& pos);

    /**
    * @brief check if a vector is on the left of another one.
    * @param p a vector used to build an other vector.
    * @param p1 a vector used to build an other vector.
    * @param p2 a vector used to build an other vector.
    * @return true if the vector is on the left, false otherwise.
    */
    bool is_on_the_left(const Vector2D *p, const Vector2D *p1, const Vector2D *p2);

    bool is_empty(const std::vector<Vector2D*> &tmp, int n);

    /**
     * @brief check if a point is inside the triangle.
     * @param p the point to check.
     * @return true if the point is inside, false otherwise.
     */
    bool is_inside(const Vector2D &p);

    /**
     * @brief check if a point is inside the circumscribed circle of the triangle.
     * @param p the point to check.
     * @return true if the point is inside, false otherwise.
     */
    bool is_inside_circle(const Vector2D &p);

//    /**
//     * @brief draw the triangle.
//     */
//    void draw();

    /**
     * @brief check if a point is common with a point of the triangle.
     * @param point the point to check.
     * @return true if it is common, false otherwise.
     */
    bool is_common_point(Vector2D* point);

    /**
     * @brief iterate over all the points of the triangle and execute the callback function each time.
     * @param cb the callback function.
     */
    void foreach_point(PointCallback cb);

    /********** Operator overloading **********/

    /**
     * @brief operator overloading to check if two triangles are equals.
     * @param triangle1 the first triangle.
     * @param triangle2 the second triangle.
     * @return true if the two triangles have all the points in common.
     */
    friend bool operator==(Triangle& triangle1, Triangle& triangle2);

    /**
     * @brief operator overloading to print a triangle.
     * @param out the output stream.
     * @param triangle the triangle to print.
     * @return the output stream.
     */
    friend std::ostream &operator<<(std::ostream &out, Triangle &triangle);

private:
    bool is_highlighted_;

    Vector2D circum_center_;

    float circum_radius_;

    bool is_delaunay_;
};

#endif //DRONEPROJECT_TRIANGLE_HPP