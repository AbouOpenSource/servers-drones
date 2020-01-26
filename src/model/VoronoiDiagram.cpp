//
// Created by LECOQ Julien on 24/01/2020.
//

#include "VoronoiDiagram.hpp"
#include "../util/VectorUtil.hpp"
#include "../core/ServiceContainer.hpp"

VoronoiDiagram::VoronoiDiagram(MyPolygon& mesh): Drawable()
{
    mesh.foreach_vertex([&mesh, this](Vector2D& vertex, unsigned int index) {
        MyPolygon* polygon = new MyPolygon(100);

        // subset of triangles of D that have Qi as vertex
//        if (index == 0)
//        {
            std::vector<Triangle> triangles = mesh.get_triangles_from(vertex);
            Triangle* triangle = left_triangle(triangles, vertex);

            if (triangle != nullptr)
            {
                Vector2D* b = next_vertex(*triangle, vertex);
                Vector2D E = *b - vertex;
                Vector2D center = Vector2D::center(vertex, *b);

                Vector2D u = right_orthogonal_vector(E);

                Vector2D Q = intersection_with_borders(center, u, 0, 0, GlutWindow::getWindowWidth(), GlutWindow::getWindowHeight());
//                std::cout << "Q: " << Q << "\n";

                // TODO Be careful, it doens't add the point to << points_to_build_polygon_ >>
                // TODO this means that the foreach method will not gives you the added point.
                add_point(Q, *polygon);
            }
            else
            {
                triangle = &triangles[0];
            }

            triangle->calculate_circle();

            while (triangles.size() > 1)
            {
                // TODO Be careful, it doens't add the point to << points_to_build_polygon_ >>
                // TODO this means that the foreach method will not gives you the added point.

                add_point(triangle->circum_center_, *polygon);
                Triangle* previous_triangle = triangle;
                triangle = right_neighbor(mesh, *triangle, vertex);
                remove_triangle(*previous_triangle, triangles);
            }

            add_point(triangle->circum_center_, *polygon);

            if (triangle != nullptr)
            {
                Vector2D* b = prev_vertex(*triangle, vertex);
                Vector2D E = *b - vertex;
                Vector2D center = Vector2D::center(vertex, *b);

                Vector2D u = right_orthogonal_vector(E);
                Vector2D Q = intersection_with_borders(center, u, 0, 0, GlutWindow::getWindowWidth(), GlutWindow::getWindowHeight());

                // TODO Be careful, it doens't add the point to << points_to_build_polygon_ >>
                // TODO this means that the foreach method will not gives you the added point.
                add_point(Q, *polygon);
            }

            remove_triangle(*triangle, triangles);
            addCornerPoints(*polygon);
//        }

        push(*polygon);
    });
}

void VoronoiDiagram::remove_triangle(Triangle& triangle, std::vector<Triangle>& triangles)
{
    auto it_triangle = triangles.begin();

    while (it_triangle != triangles.end())
    {
        if (triangle == *it_triangle)
        {
            triangles.erase(it_triangle);
            return;
        }

        it_triangle++;
    }
}
Triangle* VoronoiDiagram::right_neighbor(MyPolygon& mesh, Triangle& current, Vector2D& a)
{
    // Get the previous point.
    Vector2D* b_current = prev_vertex(current, a);

    // For each triangle and point of this triangle.
    for (Triangle& triangle: mesh.triangles_)
    {
        if (triangle == current)
        {
            continue;
        }

        // Check if the triangle own the point a.
        if (triangle.common_point(&a) && triangle.common_point(b_current))
        {
            return &triangle;
        }
    }

    return nullptr;
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
//        std::cout << triangles[i];

        Vector2D* next_point = next_vertex(triangles[i], vertex);

        for (unsigned int j = 0; j < triangles.size(); j++)
        {
            if (i != j)
            {
                if (triangles[j].common_point(next_point))
                {
//                    std::cout << "common\n\n";
                    is_shared = true;
                    break;
                }

//                std::cout << "not common\n\n";
            }
        }

        if (!is_shared)
        {
            return &triangles[i];
        }
    }

    return nullptr;
}

Vector2D* VoronoiDiagram::next_vertex(Triangle& triangle, Vector2D& vertex)
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

Vector2D* VoronoiDiagram::next_edge(Triangle triangle, Vector2D vertex)
{
    Vector2D* next_point = next_vertex(triangle, vertex);

    Vector2D* next_edge =  new Vector2D(*next_point - vertex);

    return next_edge;
}

Vector2D* VoronoiDiagram::prev_vertex(Triangle& triangle, Vector2D& vertex)
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

Vector2D* VoronoiDiagram::prev_edge(Triangle triangle, Vector2D vertex)
{
    Vector2D* prev_point = prev_vertex(triangle, vertex);

    Vector2D* prev_edge =  new Vector2D(vertex - *prev_point);

    return prev_edge;
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

void VoronoiDiagram::add_point(Vector2D A, MyPolygon& polygon)
{
    polygon.add_vertex(A);
}

void VoronoiDiagram::addCornerPoints(MyPolygon &polygon)
{
    float window_width(GlutWindow::getWindowWidth());
    float window_height(GlutWindow::getWindowHeight());

    Vector2D* previous_point;

    float x0(0);
    float y0(0);

    polygon.foreach_vertex([&](Vector2D& current_point, unsigned int index) {
        if (index == 0)
        {
            return;
        }

        if ((current_point.x_ == x0 || previous_point->x_ == x0) && (current_point.y_ == y0 || previous_point->y_ == y0))
        {
            Vector2D left_bottom_border_point(x0, y0);

            polygon.add_vertex(left_bottom_border_point);
        }
        else if ((current_point.x_ == x0 || previous_point->x_ == x0) && (current_point.y_ == window_height || previous_point->y_ == window_height))
        {
            Vector2D left_top_border_point(x0, window_height);

            polygon.add_vertex(left_top_border_point);
        }
        else if ((current_point.x_ == window_width || previous_point->x_ == window_width) && (current_point.y_ == y0 || previous_point->y_ == y0))
        {
            Vector2D right_bottom_border_point(window_width, y0);

            polygon.add_vertex(right_bottom_border_point);
        } else if ((current_point.x_ == window_width || previous_point->x_ == window_width) && (current_point.y_ == window_height || previous_point->y_ == window_height))
        {
            Vector2D right_top_border_point(window_width, window_height);

            polygon.add_vertex(right_top_border_point);
        }

        previous_point = &current_point;
    });
}

void VoronoiDiagram::push(MyPolygon& polygon)
{
    voronoi_diagram_.push_back(polygon);
}

void VoronoiDiagram::start(InputManager *input_manager, Drawable::TextureLoader texture_loader)
{
//    Drawable::start(input_manager, texture_loader);
}

void VoronoiDiagram::draw()
{
//    for (MyPolygon& polygon: voronoi_diagram_)
//    {
//        std::cout << sizeof(polygon.tab_pts_) << "\n";

//        std::cout << polygon;
//        polygon.draw();
//    }
}

void VoronoiDiagram::quit()
{
}

