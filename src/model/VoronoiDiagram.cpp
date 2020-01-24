//
// Created by LECOQ Julien on 24/01/2020.
//

#include "VoronoiDiagram.hpp"

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

        MyPolygon polygon = MyPolygon();

        // subset of triangles of D that have Qi as vertex
        std::vector<Triangle> triangles = mesh.get_triangles_from(vertex);

        Triangle triangle = left_triangle(triangles);


        std::cout << vertex << std::endl;
    });
}

Triangle VoronoiDiagram::left_triangle(std::vector<Triangle> triangles) const
{

    return Triangle();
}
