#ifndef POINTS_AND_CONVEX_POLYGONS_Polygon_HPP
#define POINTS_AND_CONVEX_POLYGONS_Polygon_HPP

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "Triangle.hpp"
#include "Server.hpp"

class Polygon
{

public:
    /********** typedef **********/
    /**
     * @brief: callback on the Vertex of the polygone.
     */
    typedef std::function<void(Vector2D& point, unsigned int index)> VertexCallback;

    /********** Constructor & destructor **********/
    explicit Polygon(int max_pts = 100);

    Polygon(std::vector<Vector2D> points, int max_pts = 100);

    ~Polygon();

    /********** Getter **********/

    std::vector<Vector2D> &get_build_points();

    std::vector<Triangle> &get_triangles();

    Vector2D *get_tab_pts();

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
    /**
     * @brief creating the triangles from polygone with the triagulation processe.
     */
    void triangulation();

    static bool polar_comparison(Vector2D p1, Vector2D p2);

    bool is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);

    vector<float> intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q);

    std::vector<float> intersections(const Vector2D& a, const Vector2D& u);

    float cross_product(const Vector2D& u, const Vector2D& v);

    bool is_inside_triangle(const Vector2D& p);

    void interior_triangulation();

    Triangle* neighbor_inside(Triangle* current);
    /**
     * @brief modify the organisation of the triangle to get right delaunay configuraton.
     * @param current: Triangle
     * @param neighbor: Trianlge
     */
    void flip(Triangle* current, Triangle* neighbor);
    /**
     * @brief make delaunay configuraton in the mesh of triangle.
     */
    void solve_delaunay();
    /**
     * @brief: check if that respests the delaunay configuration
     */
    void check_delaunay();
    /**
     * @brief like a loop, this function loop on each vertex of the polygon.
     * @param cb the callback
     */
    void foreach_vertex(VertexCallback cb);

    // Return the subset of triangles of the mesh that have v1 as vertex.
    std::vector<Triangle> get_triangles_from(Vector2D v1);

    Vector2D* next_vertex(Vector2D& vertex);
    /**
     * @brief check the Vector is in next right vector.
     * @param p the vector that we want to check if it is in the next right.
     * @return true or false.
     */
    bool is_in_side_right(const Vector2D &p);
    /**
     * @brief check the Vector is the next left vector.
     * @param p  the vector that we want to check if it is in the left right
     * @return true or false.
     */
    bool is_inside_left(const Vector2D &p);

    bool is_on_the_right(const Vector2D &p, int i);

    Vector2D* previous_vertex(Vector2D &vertex);
    /**
     * @brief: computing the area of the polygone
     * @return: a float (area)
     */
    float area();

    /********** Operator overloading **********/
    friend std::ostream &operator<<(std::ostream &out, Polygon &polygon);

private:

    int n_max_;
    int current_n_;
    float color_[4];

    Vector2D* tab_pts_;

    std::vector<Vector2D> build_points_;
    std::vector<Vector2D> interior_points_;
    std::vector<Triangle> triangles_;
};

#endif //POINTS_AND_CONVEX_POLYGONS_Polygon_HPP