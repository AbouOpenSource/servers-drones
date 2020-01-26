//
// Created by LECOQ Julien on 24/01/2020.
//

#include "VoronoiDiagram.hpp"
#include "../util/VectorUtil.hpp"
#include "../core/ServiceContainer.hpp"
#include <array>

VoronoiDiagram::VoronoiDiagram(MyPolygon& mesh, std::vector<Server> servers)
    : Drawable(),
    servers_(servers),
    left_top_border_added_(false),
    right_top_border_added_(false),
    left_bottom_border_added_(false),
    right_bottom_border_added_(false)
{
    mesh.foreach_vertex([&mesh, &servers, this](Vector2D& vertex, unsigned int index)
    {
        MyPolygon* polygon = new MyPolygon(100, servers);

        // subset of triangles of D that have Qi as vertex
        std::vector<Triangle> triangles = mesh.get_triangles_from(vertex);

        Triangle* triangle = left_triangle(triangles, vertex);
        bool is_opened = triangle != nullptr;

        if (is_opened)
        {
            Vector2D* b = next_vertex(*triangle, vertex);
            Vector2D E = *b - vertex;

            std::cout << "current vertex: " << vertex << std::endl;
            std::cout << "triangle: " << *triangle;
            std::cout << "next vertex: " << *b << std::endl;
            std::cout << "next edge: " << E << std::endl;

            Vector2D center = Vector2D::center(vertex, *b);
            std::cout << "center: " << center << std::endl;

            Vector2D u = right_orthogonal_vector(E);
            std::cout << "right orthogonal vector: " << u << std::endl;

            Vector2D Q = intersection_with_borders(center, u, 0, 0, GlutWindow::getWindowWidth(), GlutWindow::getWindowHeight());
            std::cout << "Intersection with borders: " << Q << std::endl << std::endl;

            add_point(Q, *polygon);
        }
        else
        {
            triangle = &triangles[0];
            std::cout << "no left triangle, adding the first triangle of the subset of triangles: "
                      << *triangle << std::endl;
        }

        while (triangles.size() > 1)
        {
            add_point(triangle->circum_center_, *polygon);
            Triangle* previous_triangle = triangle;

            triangle = right_neighbor(mesh, *triangle, vertex);

            remove_triangle(*previous_triangle, triangles);
        }

//         TODO Is it useful?
        add_point(triangle->circum_center_, *polygon);

            if (is_opened)
            {
                Vector2D* b = prev_vertex(*triangle, vertex);
                Vector2D E = vertex - *b;

                std::cout << "current vertex: " << vertex << std::endl;
                std::cout << "triangle: " << *triangle;
                std::cout << "prev vertex: " << *b << std::endl;
                std::cout << "prev edge: " << E << std::endl;

                Vector2D center = Vector2D::center(vertex, *b);
                std::cout << "center: " << center << std::endl;

                Vector2D u = right_orthogonal_vector(E);
                std::cout << "right orthogonal vector: " << u << std::endl;

                Vector2D Q = intersection_with_borders(center, u, 0, 0, GlutWindow::getWindowWidth(), GlutWindow::getWindowHeight());
                std::cout << "Intersection with borders: " << Q << std::endl << std::endl;

                add_point(Q, *polygon);
            }

        remove_triangle(*triangle, triangles);
        add_corner_points(*polygon);

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

Triangle* VoronoiDiagram::left_triangle(std::vector<Triangle>& triangles, Vector2D& vertex)
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
    Vector2D* next_point(nullptr);

    triangle.foreach_point([&next_point, &vertex, &triangle](Vector2D* point, unsigned int index) {
        if (*point == vertex)
        {
            next_point = triangle.ptr_[(index + 1) % 3];
        }
    });

    return next_point;
}

Vector2D* VoronoiDiagram::next_vertex(MyPolygon& polygon, Vector2D& vertex)
{
    Vector2D* next_point(nullptr);

    polygon.foreach_vertex([&next_point, &vertex, &polygon](Vector2D& point, unsigned int index) {
        if (point == vertex)
        {
            next_point = &polygon.tab_pts_[(index + 1) % polygon.points_to_build_polygon_.size()];
        }
    });

    return next_point;
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

    float k = min(k0, k1, k2, k3);

    Vector2D P = a + k * u;

    return P;
}

float VoronoiDiagram::min(float k0, float k1, float k2, float k3)
{
    std::vector<float> positive_numbers;

    if (k0 > 0)
    {
        positive_numbers.push_back(k0);
    }
    if (k1 > 0)
    {
        positive_numbers.push_back(k1);
    }
    if (k2 > 0)
    {
        positive_numbers.push_back(k2);
    }
    if (k3 > 0)
    {
        positive_numbers.push_back(k3);
    }

    float min_positive_number(-1);
    unsigned int counter(0);

    for (float positive_number: positive_numbers)
    {
        if (counter == 0)
        {
            min_positive_number = positive_number;
        }

        if (positive_number < min_positive_number)
        {
            min_positive_number = positive_number;
        }

        counter++;
    }

    return min_positive_number;
}

void VoronoiDiagram::add_point(Vector2D A, MyPolygon& polygon)
{
    polygon.add_vertex(A);
}

void VoronoiDiagram::add_corner_points(MyPolygon &polygon)
{
    float window_width(GlutWindow::getWindowWidth());
    float window_height(GlutWindow::getWindowHeight());

    Vector2D* next_point;

    float x0(0);
    float y0(0);

    polygon.foreach_vertex([&](Vector2D& current_point, unsigned int index) {
        next_point = next_vertex(polygon, current_point);

        if (((current_point.x_ == x0 && next_point->y_ == y0) || (next_point->x_ == x0 && current_point.y_ == y0)) && !left_bottom_border_added_)
        {
            left_bottom_border_added_ = true;
            Vector2D left_bottom_border_point(x0, y0);

            polygon.add_vertex(left_bottom_border_point);
        }
        else if (((current_point.x_ == x0  && next_point->y_ == window_height) || (next_point->x_ == x0 && current_point.y_ == window_height)) && !left_top_border_added_)
        {
            left_top_border_added_ = true;
            Vector2D left_top_border_point(x0, window_height);

            polygon.add_vertex(left_top_border_point);
        }
        else if (((current_point.x_ == window_width && next_point->y_ == y0) || (next_point->x_ == window_width && current_point.y_ == y0)) && !right_bottom_border_added_)
        {
            right_bottom_border_added_ = true;
            Vector2D right_bottom_border_point(window_width, y0);

            polygon.add_vertex(right_bottom_border_point);
        }
        else if (((current_point.x_ == window_width && next_point->y_ == window_height) || (next_point->x_ == window_width && current_point.y_ == window_height)) && !right_top_border_added_)
        {
            right_top_border_added_ = true;
            Vector2D right_top_border_point(window_width, window_height);

            polygon.add_vertex(right_top_border_point);
        }
        else if (!left_bottom_border_added_ && !right_bottom_border_added_ && !left_top_border_added_ && !right_top_border_added_)
        {
            std::cout << "OK" << std::endl;
            return;
        }
        else if (((current_point.x_ == x0 && next_point->x_ == window_width) || (next_point->x_ == x0 && current_point.x_ == window_width)) && !left_bottom_border_added_ && !right_bottom_border_added_)
        {
            std::cout << std::endl << "ENTERRRRRRRRRRR1" << std::endl;

            left_bottom_border_added_ = true;
            right_bottom_border_added_ = true;

            Vector2D left_bottom_border_point(x0, y0);
            Vector2D right_bottom_border_point(window_width, y0);

            polygon.add_vertex(left_bottom_border_point);
            polygon.add_vertex(right_bottom_border_point);
        }
        else if (((current_point.x_ == x0 && next_point->x_ == window_width) || (next_point->x_ == x0 && current_point.x_ == window_width)) && !left_top_border_added_ && !right_top_border_added_)
        {
            std::cout << std::endl << "ENTERRRRRRRRRRR2" << std::endl;

            left_top_border_added_ = true;
            right_top_border_added_ = true;

            Vector2D left_top_border_point(x0, window_height);
            Vector2D right_top_border_point(window_width, window_height);

            polygon.add_vertex(left_top_border_point);
            polygon.add_vertex(right_top_border_point);
        }
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
    for (MyPolygon& polygon: voronoi_diagram_)
    {
        polygon.draw();
    }
}

void VoronoiDiagram::quit()
{
}

