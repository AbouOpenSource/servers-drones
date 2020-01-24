//
// Created by LECOQ Julien on 24/01/2020.
//

#include "VoronoiDiagram.hpp"
#include "../util/VectorUtil.hpp"

// TODO PSEUDO CODE: Voronoi Diagram.
//
// Let D be a Delaunay Mesh
// For each vertex Qi of D
// Create a polygon Pi
// T = subset of triangles of D that have Qi as vertex
//         E = left edge of T
//         If E exists
// Pi.add(Intersection points between the perpendicular bisectors
//         of E and the border)
// Else E=T.first
// Einit = E
// Do
//         Pi.add(circumCenter of E)
// Eprev = E
// E = E.right neighbor
//         While E exist and E !=Einit
//         If E exists
// Pi.add(Intersection points between the perpendicular bisectors of
// The right edge of Eprev and the border)
// Else E=T.first
// Done

VoronoiDiagram::VoronoiDiagram(MyPolygon& mesh)
{
    mesh.foreach_vertex([&mesh, this](Vector2D vertex, unsigned int index) {

//        MyPolygon polygon = MyPolygon();

//         subset of triangles of D that have Qi as vertex
        std::vector<Triangle> triangles = mesh.get_triangles_from(vertex);

        Triangle triangle = left_triangle(triangles);

//        std::cout << vertex << std::endl;
    });
}

Triangle VoronoiDiagram::left_triangle(std::vector<Triangle> triangles) const
{
    return Triangle();
}

Vector2D* VoronoiDiagram::next_edge(Triangle triangle, Vector2D vertex)
{
    Vector2D* next_vertex(nullptr);

    triangle.foreach_point([&next_vertex, &vertex, &triangle](Vector2D* point, unsigned int index) {
        if (*point == vertex)
        {
            next_vertex = triangle.ptr_[(index + 1) % 3];
        }
    });

    return next_vertex;
}

Vector2D* VoronoiDiagram::prevEdge(Triangle triangle, Vector2D vertex)
{
    Vector2D* previous_vertex(nullptr);

    triangle.foreach_point([&previous_vertex, &vertex, &triangle](Vector2D* point, unsigned int index) {
        if (*point == vertex)
        {
            if (index == 0)
            {
                previous_vertex = triangle.ptr_[2];
            }
            else
            {
                previous_vertex = triangle.ptr_[index - 1];
            }
        }
    });

    return previous_vertex;
}

