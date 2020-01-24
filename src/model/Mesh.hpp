#ifndef DRONEPROJECT_MESH_HPP
#define DRONEPROJECT_MESH_HPP

#include "Triangle.hpp"
#include "Server.hpp"
#include "../view/View.hpp"

class Mesh: public View
{

public:
    std::vector<Vector2D> vertices;
    std::vector<Triangle> triangles_;

    Mesh(std::vector<Server> servers);

    Mesh(const float tab_vect[][2], int size_tab_vect, const int tab_tri[][3], int size_tab_tri);

    void onMouseMove(const Vector2D& pos);

    void draw();

    void onMouseDown(const Vector2D& pos);

    Triangle* get_triangle(const Vector2D& pos);

    void check_delaunay();
};

#endif //DRONEPROJECT_MESH_HPP
