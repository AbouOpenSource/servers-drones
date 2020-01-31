//
// Created by LECOQ Julien on 24/01/2020.
//

#ifndef DRONEPROJECT_VORONOIDIAGRAM_HPP
#define DRONEPROJECT_VORONOIDIAGRAM_HPP

#include "MyPolygon.hpp"

class VoronoiDiagram: public Drawable
{
public:
    VoronoiDiagram(MyPolygon& polygon, std::vector<Server> servers);

    void start(InputManager* input_manager, TextureLoader texture_loader);

    void draw();

    void quit();

private:

    bool left_top_border_added_;

    bool right_top_border_added_;

    bool left_bottom_border_added_;

    bool right_bottom_border_added_;

    std::vector<MyPolygon> voronoi_diagram_;

    std::vector<Server> servers_;

    Vector2D* next_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D* next_vertex(MyPolygon& polygon, Vector2D& vertex);

    Vector2D *next_edge(Triangle triangle, Vector2D vertex);

    Vector2D *prev_edge(Triangle triangle, Vector2D vertex);

    Vector2D* prev_vertex(Triangle& triangle, Vector2D& vertex);

    Vector2D intersection_with_borders(Vector2D a, Vector2D u, float x0, float y0, float x1, float y2);

    Triangle* right_neighbor(MyPolygon& mesh, Triangle& triangle, Vector2D& a);

    Triangle* left_triangle(std::vector<Triangle>& triangles, Vector2D& vertex);

    void add_point(Vector2D A, MyPolygon& polygon);

    Vector2D right_orthogonal_vector(Vector2D& vertex);

    void remove_triangle(Triangle &triangle, vector<Triangle> &triangles);

    void add_corner_points(MyPolygon& polygon);

    void push(MyPolygon& polygon);

    float min(float x0, float y0, float x1, float y1);
};


#endif //DRONEPROJECT_VORONOIDIAGRAM_HPP