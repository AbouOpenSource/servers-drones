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
//    for (Triangle triangle: mesh.triangles_)
//    {
//        std::cout << triangle << std::endl;
//    }

    mesh.foreach_vertex([&mesh, this](Vector2D vertex, unsigned int index) {
        MyPolygon* polygon = new MyPolygon(100);

        // subset of triangles of D that have Qi as vertex
        if (index == 0)
        {
            std::vector<Triangle> triangles = mesh.get_triangles_from(vertex);
            Triangle* triangle = left_triangle(triangles, vertex);

            Vector2D* b = next_vertex(*triangle, vertex);

            if (triangle != nullptr)
            {
                Vector2D E = *b - vertex;
                Vector2D center = (vertex + *b) / 2;

                Vector2D u = right_orthogonal_vector(E);

                // TODO change 1000 to the real width with the ServiceContainer, same for the height.
                Vector2D Q = intersection_with_borders(center, u, 0, 0, 1000, 800);
//                std::cout << "Q: " << Q << "\n";

                add_point(Q, *polygon);
            }
            else
            {
                triangle = &triangles[0];
            }

            while (triangles.size() > 1)
            {
                add_point(triangle->circum_center_, *polygon);
                Triangle* previous_triangle = new Triangle(triangle);
            }
        }
    });
}

Triangle* right_neighbor(MyPolygon* mesh, Triangle* triangle, Vector2D& a)
{
    //
//    ba = a;

    for (Triangle triangle: mesh->triangles_)
    {

    }
}

Vector2D VoronoiDiagram::right_orthogonal_vector(Vector2D& vertex)
{
    return Vector2D(vertex.y_, -vertex.x_);
}

Triangle* VoronoiDiagram::left_triangle(std::vector<Triangle> triangles, Vector2D& vertex)
{
    bool is_shared(false);

//    std::cout << "\n\n\n\n\n\n";
//    std::cout << "Qi point: " << vertex << "\n\n";

    for (unsigned int i = 0; i < triangles.size(); i++)
    {
        is_shared = false;
        std::cout << triangles[i];

        Vector2D* next_point = next_vertex(triangles[i], vertex);
//        std::cout << "i: "<< i << ", next point: " << *next_point << "\n";

        for (unsigned int j = 0; j < triangles.size(); j++)
        {
            if (i != j)
            {
//                std::cout << triangles[j];

//                std::cout << "j: " << j << std::endl;

                if (triangles[j].common_point(next_point))
                {
                    std::cout << "common\n\n";
                    is_shared = true;
                    break;
                }

                std::cout << "not common\n\n";
//                return &triangles[i];
            }
        }

        if (!is_shared)
        {
            return &triangles[i];
        }
    }

    return nullptr;
}

Vector2D* VoronoiDiagram::next_vertex(Triangle triangle, Vector2D vertex)
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

Vector2D* VoronoiDiagram::prev_vertex(Triangle triangle, Vector2D vertex)
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

Vector2D VoronoiDiagram::intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y1)
{
    float k0 = (x0 - a.x_) / u.x_;
    float k1 = (x1 - a.x_) / u.x_;
    float k2 = (y0 - a.y_) / u.y_;
    float k3 = (y1 - a.y_) / u.y_;

    float k = std::min({k0, k1, k2, k3});

    Vector2D P = a + k * u;

    return P;
}

void VoronoiDiagram::add_point(Vector2D A, MyPolygon& P)
{
    P.add_vertex(A);
}
