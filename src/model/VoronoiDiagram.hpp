
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

    VoronoiDiagram(Polygon& polygon);

public:

    vector<Polygon*> &get_polygons();

private:

    std::vector<Polygon*> polygons_;

    // std::vector<Server> servers_;

    bool left_top_border_added_;

    bool right_top_border_added_;

    bool left_bottom_border_added_;

    bool right_bottom_border_added_;

    Vector2D* next_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D* next_vertex(Polygon& polygon, Vector2D& vertex);

    Vector2D *next_edge(Triangle triangle, Vector2D vertex);

    Vector2D *prev_edge(Triangle triangle, Vector2D vertex);

    Vector2D* prev_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y2);

    Triangle* right_neighbor(Polygon& mesh, Triangle& triangle, Vector2D& a);

    Triangle* left_triangle(std::vector<Triangle>& triangles, Vector2D& vertex);

    void add_point(Vector2D A, Polygon& polygon);

    Vector2D right_orthogonal_vector(Vector2D& vertex);

    void remove_triangle(Triangle &triangle, vector<Triangle> &triangles);

    void add_corner_points(Polygon& polygon);

    void push(Polygon* polygon);

    float min(float x0, float y0, float x1, float y1);
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP