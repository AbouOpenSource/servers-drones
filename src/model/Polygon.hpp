#ifndef POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP
#define POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP

#include <glutWindow.h>

#include <vector>
#include "Vector2D.hpp"
#include "Triangle.hpp"
#include "Server.hpp"
#include "../view/View.hpp"

class Polygon
{

public:
    /********** Constructor & destructor **********/

    Polygon();

    Polygon(int p_max);

//    Polygon(std::vector<Vector2D> &vertices);

    ~Polygon();

    /********** Modifier **********/
    bool add_vertex(const Vector2D &p);

    void init(std::vector<Server>& servers);

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

    static bool polar_comparison(Vector2D p1, Vector2D p2);

    bool is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);

    vector<float> intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q);

    std::vector<float> intersections(const Vector2D& a, const Vector2D& u);

    float cross_product(const Vector2D& u, const Vector2D& v);

    int get_n_max() const;

    int get_current_n() const;

    const std::string get_color() const;

    Vector2D *get_tab_pts() const;

    const vector<Triangle> &get_triangles() const;

    const vector<Vector2D> &get_interior_points() const;

    const vector<Vector2D> &get_build_points() const;

    bool is_inside_triangle(const Vector2D& p);

    void set_color(const std::string& color);

    void delaunay_triangulation(std::vector<Vector2D>& relative_points);

    void delaunay_check();

private:

    int n_max_;
    int current_n_;

    std::string color_;

    Vector2D* tab_pts_;

    std::vector<Triangle> triangles_;
    std::vector<Vector2D> interior_points;
    std::vector<Vector2D> build_points;
};

#endif //POINTS_AND_CONVEX_POLYGONS_MYPOLYGON_HPP
