//
// Created by LECOQ Julien on 24/01/2020.
//

#ifndef DRONEPROJECT_VORONOIDIAGRAM_HPP
#define DRONEPROJECT_VORONOIDIAGRAM_HPP

#include "MyPolygon.hpp"

class VoronoiDiagram
{
public:
    VoronoiDiagram(MyPolygon& polygon);

    Vector2D right_orthogonal_vector(Vector2D& vertex);

    Triangle* left_triangle(std::vector<Triangle> triangles, Vector2D& vertex);

    Vector2D* next_vertex(Triangle triangle, Vector2D vertex);

    Vector2D* prev_vertex(Triangle triangle, Vector2D vertex);

    Vector2D intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y2);

    void add_point(Vector2D A, MyPolygon& P);

    Triangle* right_neighbor(MyPolygon* mesh, Triangle* triangle, Vector2D& a);

private:
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP
