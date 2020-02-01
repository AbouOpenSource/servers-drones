#ifndef POINTS_AND_CONVEX_POLYGONS_Polygon_HPP
#define POINTS_AND_CONVEX_POLYGONS_Polygon_HPP

#include <glutWindow.h>

#include "Vector2D.hpp"
#include "Triangle.hpp"
#include "Server.hpp"

class MyPolygon
{

public:
    /********** typedef **********/

    /**
     * @brief: callback on the point of the polygon.
     */
    typedef std::function<void(Vector2D& point, unsigned int index)> VertexCallback;

    /********** Constructor & destructor **********/

    /**
     * @brief a constructor to create a polygon of size 100 (number of vertices).
     * @param max_pts the maximum number of vertices.
     */
    explicit MyPolygon(int max_pts = 100);

    /**
     * @brief a constructor to create a polygon (it creates a convex hull and then a mesh).
     * @param points a list of points to create the polygon.
     * @param max_pts the maximum number of points (default 100, it can be changed later).
     */
    MyPolygon(std::vector<Vector2D> points, int max_pts = 100);

    /**
     * @brief destructor of the polygon. It destroy the pointer of the tab_pts_ variable.
     */
    ~MyPolygon();

    /********** Getter **********/

    /**
     * @brief getter for the build_points_ variable.
     * @return the build_points_ variable.
     */
    std::vector<Vector2D> &get_build_points();

    /**
     * @brief getter for the triangles_ variable.
     * @return the triangles_ variable.
     */
    std::vector<Triangle> &get_triangles();

    /**
     * @brief getter for the tab_pts_ variable.
     * @return the tab_pts_ variable..
     */
    Vector2D *get_tab_pts();

    /************ Modifiers **********/

    /**
     * @brief add a vertex to the polygon.
     * @param p the vertex to add.
     * @return true if the vertex has been added, false otherwise.
     */
    bool add_vertex(Vector2D &p);

    /**
     * @brief initialize the polygon, it create the convex hull and the mesh.
     */
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
     * @brief creating the triangles of the polygon with the triangulation process of Delaunay.
     */
    void triangulation();

    /**
     * @brief perform a polar comparison between two vectors.
     * @param p1 the first vector.
     * @param p2 the second vector.
     * @return true or false.
     */
    static bool polar_comparison(Vector2D p1, Vector2D p2);

    /**
    * @brief check if a vector is on the left of another one.
    * @param p a vector used to build an other vector.
    * @param p1 a vector used to build an other vector.
    * @param p2 a vector used to build an other vector.
    * @return true if the vector is on the left, false otherwise.
    */
    bool is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);

    vector<float> intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q);

    std::vector<float> intersections(const Vector2D& a, const Vector2D& u);

    /**
     * @brief perform a cross product between two vector.
     * @param u the first vector.
     * @param v the second vector.
     * @return the result of the cross product.
     */
    float cross_product(const Vector2D& u, const Vector2D& v);

    /**
     * @brief perform the triangulation for the interior points of the polygon.
     */
    void interior_triangulation();

    /**
     * @brief return the triangle which contain one its point inside the circumscribe circle
     * of the triangle passed in parameter.
     * @param current the triangle to check its circumscribe circle.
     * @return the neighbor triangle.
     */
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

    /**
     * @brief return the subset of triangles of the mesh that have v1 as vertex.
     * @param v1 the vertex to check.
     * @return the triangles which have v1 as common vertex.
     */
    std::vector<Triangle> get_triangles_from(Vector2D v1);

    /**
    * @brief return the vertex which follow the one passed in parameter.
    * @param vertex the vertex to check for the next one.
    * @return a pointer on the next vertex if it exist, otherwise return a nullptr.
    */
    Vector2D* next_vertex(Vector2D& vertex);

    /**
     * @brief check the Vector is in next right vector.
     * @param p the vector that we want to check if it is in the next right.
     * @return true or false.
     */
    bool is_inside_right(const Vector2D &p);

    /**
     * @brief check the Vector is the next left vector.
     * @param p  the vector that we want to check if it is in the left right
     * @return true or false.
     */
    bool is_inside_left(const Vector2D &p);

    /**
     * @brief check if a vector is on the right of another one.
     * @param p a vector used to build an other vector.
     * @param i an index to build a vector.
     * @return true if the vector is on the right, false otherwise.
     */
    bool is_on_the_right(const Vector2D &p, int i);

    /**
    * @brief return the vertex preceding the one passed in parameter.
    * @param vertex the vertex to check for the previous one.
    * @return a pointer on the previous vertex if it exist, otherwise return a nullptr.
    */
    Vector2D* previous_vertex(Vector2D &vertex);

    /**
     * @brief: computing the area of the polygon.
     * @return: a float (area)
     */
    float area();

    /**
    * @brief overload of the cout operator for this class.
    * @param out the output stream.
    * @param polygon the server to print.
    * @return the output stream.
    */
    friend std::ostream &operator<<(std::ostream &out, MyPolygon &polygon);

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