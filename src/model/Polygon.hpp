#ifndef POINTS_AND_CONVEX_POLYGONS_Polygon_HPP
#define POINTS_AND_CONVEX_POLYGONS_Polygon_HPP

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "Triangle.hpp"
#include "Server.hpp"
#include "../view/View.hpp"

class Polygon
{

private:
    /********** typedef **********/
    typedef std::function<void(Vector2D& point, unsigned int index)> VertexCallback;

public:
    int n_max_;
    int current_n_;
    float color_[4];
    Vector2D* tab_pts_;

    std::vector<Vector2D> points_to_build_polygon_;
    std::vector<Triangle> triangles_;
    std::vector<Vector2D> interior_points;

    std::vector<Server*> servers_;

    /********** Constructor & destructor **********/
    Polygon();

    Polygon(int p_max, std::vector<Server*>& servers);

    Polygon(std::vector<Server*>& servers);

    ~Polygon();

    /********** Getter **********/
    vector<Vector2D> &get_points_to_build_polygon();

    /********** Modifier **********/
    bool add_vertex(Vector2D &p);

    void init();

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

    void draw(View::DrawHelper* draw_helper);

    void triangulation();

    static bool polar_comparison(Vector2D p1, Vector2D p2);

    bool is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);

    vector<float> intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q);

    std::vector<float> intersections(const Vector2D& a, const Vector2D& u);

    float cross_product(const Vector2D& u, const Vector2D& v);

    bool is_inside_triangle(const Vector2D& p);

    void set_color(const float t_color[4]);

    void interior_triangulation();

    Triangle* neighbor_inside(Triangle* current);

    void flip(Triangle* current, Triangle* neighbor);

    void solve_delaunay();

    void delaunay_triangulation(std::vector<Vector2D>& points_relative);

    void check_delaunay();

    void onMouseMove(const Vector2D& pos);

    void foreach_vertex(VertexCallback cb);

    // Return the subset of triangles of the mesh that have v1 as vertex.
    std::vector<Triangle> get_triangles_from(Vector2D v1);

    /********** Operator overloading **********/
    friend std::ostream &operator<<(std::ostream &out, Polygon &polygon);

    Vector2D* next_vertex(Vector2D& vertex);
};

#endif //POINTS_AND_CONVEX_POLYGONS_Polygon_HPP