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

    Triangle left_triangle(std::vector<Triangle> triangles) const;

    Vector2D* next_edge(Triangle triangle, Vector2D vertex);

    Vector2D* prevEdge(Triangle triangle, Vector2D vertex);

private:
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP
