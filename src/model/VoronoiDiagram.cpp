//
// Created by LECOQ Julien on 24/01/2020.
//

#include "VoronoiDiagram.hpp"
#include <array>

VoronoiDiagram::VoronoiDiagram()
    : left_top_border_added_(false),
    right_top_border_added_(false),
    left_bottom_border_added_(false),
    right_bottom_border_added_(false)
{}

void VoronoiDiagram::init(MyPolygon* base_polygon, unsigned int width, unsigned int heigth)
{
    base_polygon->foreach_vertex([this, base_polygon, &width, &heigth](Vector2D &vertex, unsigned int index) {
        auto *polygon = new MyPolygon();
        // subset of triangles of D that have Qi as vertex
        std::vector<Triangle> triangles = base_polygon->get_triangles_from(vertex);

        Triangle *triangle = left_triangle(triangles, vertex);
        bool is_opened = triangle != nullptr;

        if (is_opened) {
            Vector2D *b = next_vertex(*triangle, vertex);
            Vector2D E = *b - vertex;
            Vector2D center = Vector2D::center(vertex, *b);
            Vector2D u = right_orthogonal_vector(E);
            Vector2D Q = intersection_with_borders(center, u, 0, 0, width, heigth);

            add_point(Q, polygon);
        } else {
            triangle = &triangles[0];
        }

        while (triangles.size() > 1) {
            add_point(triangle->get_circum_center(), polygon);
            Triangle *previous_triangle = triangle;

            triangle = right_neighbor(base_polygon, *triangle, vertex);

            remove_triangle(*previous_triangle, triangles);
        }

        // TODO Is it useful?
        add_point(triangle->get_circum_center(), polygon);

        if (is_opened) {
            Vector2D *b = previous_vertex(*triangle, vertex);
            Vector2D E = vertex - *b;
            Vector2D center = Vector2D::center(vertex, *b);
            Vector2D u = right_orthogonal_vector(E);
            Vector2D Q = intersection_with_borders(center, u, 0, 0, width, heigth);

            add_point(Q, polygon);
        }

        remove_triangle(*triangle, triangles);
        add_corner_points(polygon, width, heigth);

        push(polygon);
    });

}

void VoronoiDiagram::remove_triangle(Triangle &triangle, std::vector<Triangle> &triangles)
{
    auto it_triangle = triangles.begin();

    while (it_triangle != triangles.end()) {
        if (triangle == *it_triangle) {
            triangles.erase(it_triangle);
            return;
        }

        it_triangle++;
    }
}

Triangle *VoronoiDiagram::right_neighbor(MyPolygon* mesh, Triangle &current, Vector2D &a)
{
    // Get the previous point.
    Vector2D *b_current = previous_vertex(current, a);

    // For each triangle and point of this triangle.
    for (Triangle &triangle: mesh->get_triangles()) {
        if (triangle == current) {
            continue;
        }

        // Check if the triangle own the point a.
        if (triangle.is_common_point(&a) && triangle.is_common_point(b_current)) {
            return &triangle;
        }
    }

    return nullptr;
}

Vector2D VoronoiDiagram::right_orthogonal_vector(Vector2D &edge)
{
    return Vector2D(edge.y_, -edge.x_);
}

Triangle *VoronoiDiagram::left_triangle(std::vector<Triangle> &triangles, Vector2D &vertex)
{
    bool is_shared(false);

//    std::cout << "\n\n\n\n\n\n";
//    std::cout << "Qi point: " << vertex << "\n\n";

    for (unsigned int i = 0; i < triangles.size(); i++) {
        is_shared = false;
//        std::cout << triangles[i];

        Vector2D *next_point = next_vertex(triangles[i], vertex);

        for (unsigned int j = 0; j < triangles.size(); j++) {
            if (i != j) {
                if (triangles[j].is_common_point(next_point)) {
//                    std::cout << "common\n\n";
                    is_shared = true;
                    break;
                }

//                std::cout << "not common\n\n";
            }
        }

        if (!is_shared) {
            return &triangles[i];
        }
    }

    return nullptr;
}

Vector2D *VoronoiDiagram::next_vertex(Triangle &triangle, Vector2D &vertex)
{
    Vector2D *next_point(nullptr);

    triangle.foreach_point([&next_point, &vertex, &triangle](Vector2D *point, unsigned int index) {
        if (*point == vertex) {
            next_point = triangle.ptr_[(index + 1) % 3];
        }
    });

    return next_point;
}

Vector2D *VoronoiDiagram::next_vertex(MyPolygon* polygon, Vector2D &vertex)
{
    Vector2D *next_point(nullptr);

    polygon->foreach_vertex([&next_point, &vertex, &polygon](Vector2D &point, unsigned int index) {
        if (point == vertex) {
            next_point = &polygon->get_tab_pts()[(index + 1) % polygon->get_build_points().size()];
        }
    });

    return next_point;
}

Vector2D *VoronoiDiagram::next_edge(Triangle triangle, Vector2D vertex)
{
    Vector2D *next_point = next_vertex(triangle, vertex);

    Vector2D *next_edge = new Vector2D(*next_point - vertex);

    return next_edge;
}

Vector2D *VoronoiDiagram::previous_vertex(Triangle &triangle, Vector2D &vertex)
{
    Vector2D *previous_vertex(nullptr);

    triangle.foreach_point([&previous_vertex, &vertex, &triangle](Vector2D *point, unsigned int index) {
        if (*point == vertex) {
            if (index == 0) {
                previous_vertex = triangle.ptr_[2];
            } else {
                previous_vertex = triangle.ptr_[index - 1];
            }
        }
    });

    return previous_vertex;
}

Vector2D *VoronoiDiagram::previous_edge(Triangle triangle, Vector2D vertex)
{
    Vector2D *prev_point = previous_vertex(triangle, vertex);

    Vector2D *prev_edge = new Vector2D(vertex - *prev_point);

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

    if (k0 > 0) {
        positive_numbers.push_back(k0);
    }
    if (k1 > 0) {
        positive_numbers.push_back(k1);
    }
    if (k2 > 0) {
        positive_numbers.push_back(k2);
    }
    if (k3 > 0) {
        positive_numbers.push_back(k3);
    }

    float min_positive_number(-1);
    unsigned int counter(0);

    for (float positive_number: positive_numbers) {
        if (counter == 0) {
            min_positive_number = positive_number;
        }

        if (positive_number < min_positive_number) {
            min_positive_number = positive_number;
        }

        counter++;
    }

    return min_positive_number;
}

void VoronoiDiagram::add_point(Vector2D A, MyPolygon* polygon)
{
    polygon->add_vertex(A);
}

void VoronoiDiagram::add_corner_points(MyPolygon* polygon, float width, float height)
{
    Vector2D* next_point;

    float x0(0);
    float y0(0);

    polygon->foreach_vertex([&](Vector2D& current_point, unsigned int index) {
        next_point = next_vertex(polygon, current_point);

        if (((current_point.x_ == x0 && next_point->y_ == y0) || (next_point->x_ == x0 && current_point.y_ == y0)) && !left_bottom_border_added_) {
            left_bottom_border_added_ = true;
            Vector2D left_bottom_border_point(x0, y0);

            polygon->add_vertex(left_bottom_border_point);
        } else if (((current_point.x_ == x0  && next_point->y_ == height) || (next_point->x_ == x0 && current_point.y_ == height)) && !left_top_border_added_) {
            left_top_border_added_ = true;
            Vector2D left_top_border_point(x0, height);

            polygon->add_vertex(left_top_border_point);
        } else if (((current_point.x_ == width && next_point->y_ == y0) || (next_point->x_ == width && current_point.y_ == y0)) && !right_bottom_border_added_) {
            right_bottom_border_added_ = true;
            Vector2D right_bottom_border_point(width, y0);

            polygon->add_vertex(right_bottom_border_point);
        } else if (((current_point.x_ == width && next_point->y_ == height) || (next_point->x_ == width && current_point.y_ == height)) && !right_top_border_added_) {
            right_top_border_added_ = true;
            Vector2D right_top_border_point(width, height);

            polygon->add_vertex(right_top_border_point);
        } else if (((current_point.x_ == x0 && next_point->x_ == width) || (next_point->x_ == x0 && current_point.x_ == width))) {
            if (polygon->previous_vertex(current_point)->y_>current_point.y_) {
                if (!right_bottom_border_added_) {
                    right_bottom_border_added_ = true;
                    Vector2D right_bottom_border_point(width, y0);
                    polygon->add_vertex(right_bottom_border_point);
                }
                if (!left_bottom_border_added_) {
                    left_bottom_border_added_ = true;
                    Vector2D left_bottom_border_point(x0, y0);
                    polygon->add_vertex(left_bottom_border_point);
                }
            } else if (polygon->previous_vertex(*next_point)->y_<next_point->y_) {
                if (!right_top_border_added_) {
                    right_top_border_added_ = true;
                    Vector2D right_top_border_point(width, height);
                    polygon->add_vertex(right_top_border_point);
                }
                if (!left_top_border_added_) {
                    left_top_border_added_ = true;
                    Vector2D left_top_border_point(x0, height);
                    polygon->add_vertex(left_top_border_point);
                }
            }
        } else if (((current_point.y_ == y0 && next_point->y_ == height) || (next_point->y_ == y0 && current_point.y_ == height))) {
            if (polygon->previous_vertex(current_point)->x_>current_point.x_) {
                if (!left_top_border_added_) {
                    left_top_border_added_ = true;
                    Vector2D left_top_border_point(x0, height);
                    polygon->add_vertex(left_top_border_point);
                }
                if (!left_bottom_border_added_) {
                    left_bottom_border_added_ = true;
                    Vector2D left_bottom_border_point(x0, y0);
                    polygon->add_vertex(left_bottom_border_point);
                }
            } else if (polygon->previous_vertex(*next_point)->x_<next_point->y_) {
                if (!right_top_border_added_) {
                    right_top_border_added_ = true;
                    Vector2D right_top_border_point(width, height);
                    polygon->add_vertex(right_top_border_point);
                }
                if (!right_bottom_border_added_) {
                    right_bottom_border_added_ = true;
                    Vector2D right_bottom_border_point(width, y0);
                    polygon->add_vertex(right_bottom_border_point);
                }
            }
        }
    });
}

void VoronoiDiagram::push(MyPolygon *polygon)
{
    polygons_.push_back(polygon);
}

vector<MyPolygon*> &VoronoiDiagram::get_polygons()
{
    return polygons_;
}
