#ifndef POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP
#define POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "Triangle.hpp"
#include "Server.hpp"

//const float BLACK[4] = { 0.0, 0.0, 0.0, 1.0};
//const float RED[4] = { 1.0, 0.0, 0.0, 1.0};
//const float YELLOW[4] = { 1.0, 1.0, 0.0, 1.0};
//const float GREEN[4] = { 0.0, 1.0, 0.0, 1.0};
//const float BLUE[4] = { 0.0, 0.0, 1.0, 1.0};

class Polygon
{
    Vector2D* tab_pts_;
    int n_max_;
    int current_n_;
    std::vector<Triangle> arr_triangle_;
    float color[4];

    std::vector<Vector2D> points_to_build_polygon_;

public:
    /********** Constructor & destructor **********/
    Polygon(int p_max);

    Polygon(std::vector<Server>& servers);

//    Polygon(std::vector<Vector2D> &vertices);

    ~Polygon();

    /********** Modifier **********/
    bool add_vertex(const Vector2D &p);
    void draw();

    /**
     * @brief Check if the vertex p is inside the polygon.
     * @param p the vertex to check.
     * @return true if the vertex p is inside, false otherwise.
     */
    bool is_inside(const Vector2D& p);

    /**
    * @brief Test if the vertex is on the left of the vertex p.
    * @param p
    * @param i
    * @return true if the vertex is on the left, false otherwise
    */
    bool is_on_the_left(const Vector2D& p, int i);

    /**
    * @brief check if the polygon is convex.
    * @return true if the polygon is convex, false otherwise.
    */
    bool is_convex();

    void triangulation();

    static bool polarComparison(Vector2D p1, Vector2D p2);

    bool is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);

    vector<float> intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q);

    std::vector<float> intersections(const Vector2D& a, const Vector2D& u);

    float cross_product(const Vector2D& u, const Vector2D& v);

    bool is_inside_triangle(const Vector2D& p);

    void set_color(const float t_color[4]);
};

#endif //POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP
