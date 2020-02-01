
//
// Created by LECOQ Julien on 24/01/2020.
//

#ifndef DRONEPROJECT_VORONOIDIAGRAM_HPP
#define DRONEPROJECT_VORONOIDIAGRAM_HPP

#include <vector>
#include "Polygon.hpp"
#include "Vector2D.hpp"
#include "Triangle.hpp"

class VoronoiDiagram
{

public:

    VoronoiDiagram();

    void init(Polygon* base_polygon, unsigned int width, unsigned int height);

    vector<Polygon*> &get_polygons();

private:

    std::vector<Polygon*> polygons_;

    bool left_top_border_added_;

    bool right_top_border_added_;

    bool left_bottom_border_added_;

    bool right_bottom_border_added_;

    /**
    * @brief return the vertex which follow the one passed in parameter.
    * @param triangle the triangle where we want to get the next vertex.
    * @param vertex the vertex to check for the next one.
    * @return a pointer on the next vertex if it exist, otherwise return a nullptr.
    */
    Vector2D* next_vertex(Triangle& triangle, Vector2D& vertex);

    /**
    * @brief return the vertex which follow the one passed in parameter.
    * @param polygon the polygon where we want to get the next vertex.
    * @param vertex the vertex to check for the next one.
    * @return a pointer on the next vertex if it exist, otherwise return a nullptr.
    */
    Vector2D* next_vertex(Polygon* polygon, Vector2D& vertex);

    /**
     * @brief return the next edge of the vertex passed in parameter.
     * @param triangle the triangle where we want to get the next edge.
     * @param vertex the vertex to check for the next edge.
     * @return a pointer to the next edge if it exist, otherwise return a nullptr.
     */
    Vector2D *next_edge(Triangle triangle, Vector2D vertex);

    /**
    * @brief return the previous edge of the vertex passed in parameter.
    * @param triangle the triangle where we want to get the previous edge.
    * @param vertex the vertex to check for the previous edge.
    * @return a pointer to the previous edge if it exist, otherwise return a nullptr.
    */
    Vector2D *previous_edge(Triangle triangle, Vector2D vertex);

    /**
    * @brief return the vertex preceding the one passed in parameter.
    * @param triangle the triangle where we want to get the previous vertex.
    * @param vertex the vertex to check for the previous one.
    * @return a pointer on the previous vertex if it exist, otherwise return a nullptr.
    */
    Vector2D* previous_vertex(Triangle& triangle, Vector2D& vertex);

    /**
     * @brief return the first intersection point with the border from two vectors.
     * @param a the first vector.
     * @param u the second vector.
     * @param x0 min x border of the screen.
     * @param y0 min y border of the screen.
     * @param x1 max x border of the screen.
     * @param y2 max y border of the screen.
     * @return the intersection point.
     */
    Vector2D intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y2);

    /**
     * @brief returns the triangle that share the edge (b, a) of "triangle“.
     * @param mesh the mesh where the triangle is.
     * @param triangle the triangle to get its right neighbor.
     * @param a the vertex to get the edge (b, a).
     * @return returns the triangle that share the edge (b, a) of "triangle" (or ∅ if it does not exists).
     */
    Triangle* right_neighbor(Polygon* mesh, Triangle& triangle, Vector2D& a);

    /**
     * @brief return the triangle of the subset of triangle "triangles" (sharing a same point "vertex") that has no left neighbor.
     * @param triangles the subset of triangles.
     * @param vertex the vertex in shared.
     * @return the left triangle.
     */
    Triangle* left_triangle(std::vector<Triangle>& triangles, Vector2D& vertex);

    /**
     * @brief add a vertex to a polygon.
     * @param A the vertex to add.
     * @param polygon the polygon where the point will be add.
     */
    void add_point(Vector2D A, Polygon* polygon);

    /**
     * @brief return a vector v which is orthogonal to the edge E(a, b) (and
     * is directed to the right of E)
     * @param edge the edge E(a, b).
     * @return the orthogonal vector.
     */
    Vector2D right_orthogonal_vector(Vector2D& edge);

    /**
     * @brief remove the triangle "triangle" from the list "triangles".
     * @param triangle the triangle to remove.
     * @param triangles the list where we must remove the triangle.
     */
    void remove_triangle(Triangle &triangle, vector<Triangle> &triangles);

    /**
     * @brief add corner point to the polygon "polygon".
     * @param polygon the polygon where we must add the point.
     * @param width the width of the window.
     * @param height the height of the window.
     */
    void add_corner_points(Polygon* polygon, float width, float height);

    /**
     * @brief push a polygon inside the list of polygon "polygons_"
     * @param polygon the polygon to add.
     */
    void push(Polygon* polygon);

    /**
     * @brief return the minimum positive number from the 4 variables passed in parameter.
     * @param x0 first number
     * @param y0 second number
     * @param x1 third number
     * @param y1 fourth number
     * @return the minimum positive number from the 4 variables.
     */
    float min(float x0, float y0, float x1, float y1);
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP