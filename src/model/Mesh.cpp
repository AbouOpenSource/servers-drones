#include "Mesh.hpp"

Mesh::Mesh(const float tab_vect[][2], int size_tab_vect, const int tab_tri[][3], int size_tab_tri)
{
    for (int i = 0; i < size_tab_vect; i++)
    {
        Vector2D vertex = Vector2D{static_cast<int>(tab_vect[i][0]), static_cast<int>(tab_vect[i][1])};
        vertices.push_back(vertex);
    }

    for (int i = 0; i < size_tab_tri; i++)
    {
        Vector2D* first_vertex = &vertices[tab_tri[i][0]];
        Vector2D* second_vertex = &vertices[tab_tri[i][1]];
        Vector2D* third_vertex = &vertices[tab_tri[i][2]];

        Triangle triangle = Triangle(first_vertex, second_vertex, third_vertex);
        triangles_.push_back(triangle);
    }

    check_delaunay();
}

void Mesh::onMouseMove(const Vector2D& pos)
{
    for (auto& triangle: triangles_)
    {
        triangle.on_mouse_move(pos);
    }
}

void Mesh::draw()
{
    for (auto& triangle: triangles_)
    {
        triangle.draw();
    }

    for (auto& triangle: triangles_)
    {
        triangle.draw_circle();
    }
}

void Mesh::onMouseDown(const Vector2D& pos)
{
    Triangle *triangle = get_triangle(pos);

//        if (triangle)
//        {
//            cout << "clicked" << triangle->whoami(vertices_) << endl;
//            if (!triangle->is_delaunay_)
//            {
//                triangle* triangle_neighbor = neighbor_inside(triangle);
//
//                if (triangle_neighbor)
//                {
//                    cout << "Neighbor:" << triangle_neighbor->whoami(vertices_) << endl;
//
//                    flip(triangle, triangle_neighbor);
//                    check_delaunay();
//                }
//            }
//        }
}

Triangle* Mesh::get_triangle(const Vector2D& pos)
{
    auto triangle_iterator = triangles_.begin();

    while (triangle_iterator != triangles_.end() && !triangle_iterator->is_inside(pos))
    {
        triangle_iterator++;
    }

    return &(*triangle_iterator);
}

void Mesh::check_delaunay()
{
    auto t = triangles_.begin();

    while (t != triangles_.end())
    {
        t->check_delaunay(vertices);
        t++;
    }
}