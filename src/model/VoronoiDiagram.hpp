//
// Created by LECOQ Julien on 24/01/2020.
//

#ifndef DRONEPROJECT_VORONOIDIAGRAM_HPP
#define DRONEPROJECT_VORONOIDIAGRAM_HPP

#include "MyPolygon.hpp"

class VoronoiDiagram: public Drawable
{
public:
    VoronoiDiagram(MyPolygon& polygon);

    void start(InputManager* input_manager, TextureLoader texture_loader);

    void draw();

    void quit();

private:
    std::vector<MyPolygon> voronoi_diagram_;

    Vector2D* next_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D *next_edge(Triangle triangle, Vector2D vertex);

    Vector2D *prev_edge(Triangle triangle, Vector2D vertex);

    Vector2D* prev_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y2);

    Triangle* right_neighbor(MyPolygon& mesh, Triangle& triangle, Vector2D& a);

    Triangle* left_triangle(std::vector<Triangle> triangles, Vector2D& vertex);

    void add_point(Vector2D A, MyPolygon& polygon);

    Vector2D right_orthogonal_vector(Vector2D& vertex);

    void remove_triangle(Triangle &triangle, vector<Triangle> &triangles);

    void addCornerPoints(MyPolygon& polygon);

    void push(MyPolygon& polygon);
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP
