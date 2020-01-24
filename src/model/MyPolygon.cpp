#include <stack>
#include <algorithm>
#include <cstring>
#include <list>
#include "MyPolygon.hpp"
#include "../util/VectorUtil.hpp"
#include <array>

MyPolygon::MyPolygon()
{
}

MyPolygon::MyPolygon(int p_max)
        : tab_pts_{new Vector2D[p_max]},
          n_max_{p_max},
          current_n_{0}
{
    set_color(YELLOW);
}

MyPolygon::MyPolygon(std::vector<Server>& servers): Drawable()
{
    std::vector<Vector2D> points;

    for (const Server &server: servers) {
        points.push_back(server.getCurrentPosition());
    }

    set_color(YELLOW);

//    assert(points.size() > 3);
    points_to_build_polygon_ = points;

    auto p = points.begin();
    auto pymin = points.begin();

    // find point with minimal y and swap with first point
    while (p != points.end())
    {
        if (p->y_ < pymin->y_)
        {
            pymin = p;
        }
        p++;
    }

    // Swap
    if (pymin != points.begin())
        iter_swap(points.begin(), pymin);

    Vector2D origin{points.begin()->x_, points.begin()->y_};

    // Copy points in a set of points relative to points[0]
    vector<Vector2D> pointsRelative;

    for (auto pOrig: points)
        pointsRelative.push_back(Vector2D{pOrig.x_ - origin.x_, pOrig.y_ - origin.y_});

    // Sorting point with angular criteria.
    sort(pointsRelative.begin() + 1, pointsRelative.end(), polar_comparison);

    std::stack<Vector2D*> CHstack;
    Vector2D *top_1, *top;
    CHstack.push(&pointsRelative[0]);
    CHstack.push(&pointsRelative[1]);
    CHstack.push(&pointsRelative[2]);

    // TODO START DELAUNAY TRIANGULATION.
    vector<Vector2D>::iterator pi = pointsRelative.begin() + 3;

    while (pi != pointsRelative.end())
    {
        // Extract top and top_1.
        top = CHstack.top();
        CHstack.pop();
        top_1 = CHstack.top();
        CHstack.push(top);

        while (!is_on_the_left(&(*pi), top_1, top))
        {
            // Add interior point
            const Vector2D interior_point(top->x_ + origin.x_, top->y_ + origin.y_);
            interior_points.push_back(interior_point);

            CHstack.pop();
            // Update values of top and top_1.
            top = CHstack.top();
            CHstack.pop();
            top_1 = CHstack.top();
            CHstack.push(top);
        }

        CHstack.push(&(*pi));
        pi++;
    }

    // Get stack points to create current polygon.
    current_n_ = CHstack.size();
    n_max_ = current_n_;
    tab_pts_ = new Vector2D[n_max_ + 1];

    int i = current_n_ - 1;

    while (!CHstack.empty())
    {
        tab_pts_[i--] = *(CHstack.top()) + origin; // Place the popped point in the global referential.
        CHstack.pop();
    }

    tab_pts_[current_n_] = tab_pts_[0];
    // TODO END DELAUNAY TRIANGULATION
}

MyPolygon::~MyPolygon()
{
    delete [] tab_pts_;
}

bool MyPolygon::polar_comparison(Vector2D p1, Vector2D p2)
{
    double a1 = asin(p1.y_ / sqrt(p1.x_ * p1.x_ + p1.y_ * p1.y_));
    if (p1.x_ < 0.0)
        a1 = M_PI - a1;

    double a2 = asin(p2.y_ / sqrt(p2.x_ * p2.x_ + p2.y_ * p2.y_));
    if (p2.x_ < 0.0)
        a2 = M_PI - a2;

    return a1 < a2;
}

bool MyPolygon::is_on_the_left(const Vector2D& p, int i)
{
    Vector2D ab = tab_pts_[i + 1] - tab_pts_[i],
            ap = p - tab_pts_[i];

    return cross_product(ab, ap) >= 0;
}

bool MyPolygon::is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2)
{
    Vector2D ab = *p2 - *p1,
            ap = *p - *p1;

    return cross_product(ab, ap) >= 0;
//    (ab.x_ * ap.y_ - ab.y_ * ap.x_) >= 0;
}

bool MyPolygon::is_convex()
{
    unsigned int i = 0;

    while (i < current_n_ && is_on_the_left(tab_pts_[(i + 2) % current_n_], i))
        i++;

    return i == current_n_;
}

bool MyPolygon::add_vertex(const Vector2D &p)
{
//    if (n_max_ == current_n_ - 2)
//        return false;

    if(current_n_ == n_max_)
        return false;

    tab_pts_[current_n_++] = p;
    tab_pts_[current_n_] = tab_pts_[0];

    return true;
}

// Complexity is N because for each edge and there is N edges.
bool MyPolygon::is_inside(const Vector2D& p)
{
    int i = 0;
    while (i < current_n_ && is_on_the_left(p, i))
        i++;

    return i == current_n_;
}

bool MyPolygon::is_inside_triangle(const Vector2D& p)
{
    auto triangle = triangles_.begin();

    while (triangle != triangles_.end() && !(*triangle).is_inside(p))
        triangle++;

    return triangle != triangles_.end();
}

void MyPolygon::set_color(const float t_color[4])
{
    memcpy(color, t_color, 4 * sizeof(float));
}

void MyPolygon::draw()
{
    if (triangles_.empty())
    {
        triangulation();
        interior_triangulation();
        solve_delaunay();
        check_delaunay();
    }

    for (auto& triangle: triangles_)
    {
        triangle.draw();
    }

    // Draw the interior.
//    glColor3fv(color);
//
//    glBegin(GL_TRIANGLES);
//    for (auto t: triangles_)
//    {
//        glVertex2f(t.ptr_[0]->x_, t.ptr_[0]->y_);
//        glVertex2f(t.ptr_[1]->x_, t.ptr_[1]->y_);
//        glVertex2f(t.ptr_[2]->x_, t.ptr_[2]->y_);
//    }
//    glEnd();

    // Draw the border
//    glColor3fv(BLACK);
//    glLineWidth(3);

    // Draw the triangles.
//    glBegin(GL_LINE_LOOP);
//    for (auto t: triangles_)
//    {
//        glVertex2f(t.ptr_[0]->x_, t.ptr_[0]->y_);
//        glVertex2f(t.ptr_[1]->x_, t.ptr_[1]->y_);
//        glVertex2f(t.ptr_[2]->x_, t.ptr_[2]->y_);
//    }
//    for (int i = 0; i < current_n_; i++)
//    {
//        glVertex2f(tab_pts_[i].x_, tab_pts_[i].y_);
//    }
//    glEnd();

    // Draw the number of points.
    glLineWidth(1);
    for (int i = 0; i < current_n_; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(tab_pts_[i].x_ - 10, tab_pts_[i].y_ - 10);
        glVertex2f(tab_pts_[i].x_ + 10, tab_pts_[i].y_ + 10);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(tab_pts_[i].x_ + 10, tab_pts_[i].y_ - 10);
        glVertex2f(tab_pts_[i].x_ - 10, tab_pts_[i].y_ + 10);
        glEnd();

        GlutWindow::drawText(tab_pts_[i].x_ - 10, tab_pts_[i].y_, to_string(i), GlutWindow::ALIGN_RIGHT);
    }

    // TODO
    for (Vector2D points: points_to_build_polygon_)
    {
        glColor3fv(RED);
        GlutWindow::fillEllipse(points.x_, points.y_, 2.5, 2.5);
    }
}

vector<float> MyPolygon::intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q)
{
    std::vector<float> k;

    Vector2D pq = q - p;
    Vector2D ap = p - a;

    float det = cross_product(u, pq);

    if (det == 0.0)
        return k;

    k.push_back(cross_product(ap, pq) / det); // k1: am = k1 x u
    k.push_back(cross_product(ap, u) / det); // k2: pm = k2 x pq

    return k;
}

std::vector<float> MyPolygon::intersections(const Vector2D& a, const Vector2D& u)
{
    std::vector<float> k1k2;
    std::vector<float> kres;

    for (int i = 0; i < current_n_; ++i)
    {
        k1k2 = intersect(a, u, tab_pts_[i], tab_pts_[i + 1]);
        std::cout << "Intersection " << i << ":" << k1k2[0] << ";" << k1k2[1] << std::endl;

        if (k1k2.size() == 2 && k1k2[1] >= 0.0 && k1k2[1] <= 1.0)
        {
            auto it = kres.begin();
            auto prev_it = kres.begin();

            while (it != kres.end() && (*it) < k1k2[0])
            {
                prev_it = it;
                it++;
            }

            kres.insert(prev_it, k1k2[0]);
        }
    }

    for (auto p: kres)
        std::cout << p << std::endl;

    return kres;
}

void MyPolygon::solve_delaunay()
{
    std::list<Triangle*> processList;
    auto t = triangles_.begin(); // copy tabTriangles in a list

    while (t != triangles_.end())
    {
        processList.push_back(&(*t));
        t++;
    }

    while (processList.size() > 1)
    {
        // while a triangle is in the list
        Triangle *current = processList.front(); // pop current
        processList.pop_front();

        if (!current->is_delaunay_)
        {
            // TODO Solve the bug of the infinite loop when we add more servers.

            // if current is not Delaunay.
            Triangle *Tneighbor = neighbor_inside(current);

            if (Tneighbor!=nullptr)
            {
                // and if a neighbor is available
                flip(current, Tneighbor); // flip the common edge

                // remove Tneighbor form the list
                auto tr=processList.begin();
                while (tr!=processList.end() && (*tr)!=Tneighbor) tr++;
                if (tr!=processList.end()) processList.erase(tr);
            }
            else
                processList.push_back(current); // postpone the treatment
        }
    }
}

Triangle* MyPolygon::neighbor_inside(Triangle* current)
{
    // For each triangle.
    for (Triangle &triangle: triangles_)
    {
        // If the triangle is the one passed in parameter.
        if (&triangle == current)
            continue;

        int common_points(0);
        bool point_inside_circle(false);

        // For each point of the triangle.
        for (Vector2D* point: triangle.ptr_)
        {
            // If the point is inside the circumscribe circle of the current triangle.
            if (current->is_inside_circle(*point))
                point_inside_circle = true;

            // If the point is a common point with the triangle passed in parameter.
            if (current->common_point(point))
                common_points++;
        }

        // Found a triangle.
        if (common_points == 2 && point_inside_circle)
            return &triangle;
    }

    // No triangle found.
    return nullptr;
}

void MyPolygon::flip(Triangle* current, Triangle* neighbor)
{
    std::vector<unsigned int> index_common_points_current;
    unsigned int index_no_common_points_current;

    current->foreach_point([&](Vector2D* point, unsigned int index) {
        if (neighbor->common_point(point))
        {
            index_common_points_current.push_back(index);
        }
        else
        {
            index_no_common_points_current = index;
        }
    });

    std::vector<unsigned int> index_common_points_neighbor;
    unsigned int index_no_common_points_neighbor;

    neighbor->foreach_point([&](Vector2D* point, unsigned int index) {
        if (current->common_point(point))
        {
            index_common_points_neighbor.push_back(index);
        }
        else
        {
            index_no_common_points_neighbor = index;
        }
    });

    if (current->ptr_[index_common_points_current[0]] == neighbor->ptr_[index_common_points_neighbor[0]])
    {
        neighbor->ptr_[index_common_points_neighbor[1]] = current->ptr_[index_no_common_points_current];
    }
    else
    {
        neighbor->ptr_[index_common_points_neighbor[0]] = current->ptr_[index_no_common_points_current];
    }

    current->ptr_[index_common_points_current[0]] = neighbor->ptr_[index_no_common_points_neighbor];
}

void MyPolygon::triangulation()
{
    std::vector<Vector2D*> tmp;

    // copy the list of vertices in the tmp list.
    for (int i = 0; i < current_n_; i++)
    {
        tmp.push_back(&(tab_pts_[i]));
    }

    int n = current_n_;

    // while we can add a triangle to tabTriangle.
    while (n > 2)
    {
        int i = 0;
        auto p = tmp.begin();
        bool test;
        // create a triangle using p, p+1 and p+2 as vertices
        Triangle T(*p, *(p + 1), *(p + 2));

        // Search a triangle without another points inside
        do {
            test = !T.is_empty(tmp, i + 3);
            if (test) {
                i++;
                p++;
                T = Triangle(*p, *(p + 1), *(p + 2));
            }
        } while (i < n - 2 && test);

        assert(i < n - 2);

        // Add T to tabTriangles.
        triangles_.push_back(T);
        tmp.erase(p + 1); // remove point(p + 1) from tmp.
        n--; // or n = tmp.size().
    }
//    neighbor_inside(&triangles_[0]);
}

void MyPolygon::interior_triangulation()
{
    for (Vector2D interior_point: interior_points)
    {
        auto it_triangle = triangles_.begin();

        while (it_triangle != triangles_.end())
        {
            if (it_triangle->is_inside(interior_point))
            {
                Vector2D* p1_triangle = it_triangle->ptr_[0];
                Vector2D* p2_triangle = it_triangle->ptr_[1];
                Vector2D* p3_triangle = it_triangle->ptr_[2];
                Vector2D *interior = new Vector2D(interior_point.x_, interior_point.y_);

                Triangle triangle1 = Triangle(p1_triangle, p2_triangle, interior);
                Triangle triangle2 = Triangle(p2_triangle, p3_triangle, interior);
                Triangle triangle3 = Triangle(p3_triangle, p1_triangle, interior);

                it_triangle = triangles_.erase(it_triangle);

                triangles_.push_back(triangle1);
                triangles_.push_back(triangle2);
                triangles_.push_back(triangle3);

                break;
            }
            else
            {
                ++it_triangle;
            }
        }
    }
}

float MyPolygon::cross_product(const Vector2D& u, const Vector2D& v)
{
    return (u.x_ * v.y_ - u.y_ * v.x_);
}

void MyPolygon::onMouseMove(const Vector2D& pos)
{
    for (Triangle& triangle: triangles_)
    {
        triangle.on_mouse_move(pos);
    }
}

void MyPolygon::foreach_vertex(VertexCallback cb)
{
    for (unsigned int i = 0; i < points_to_build_polygon_.size(); i++)
    {
        cb(points_to_build_polygon_[i], i);
    }
}

std::vector<Triangle> MyPolygon::get_triangles_from(Vector2D v1)
{
    std::vector<Triangle> triangles;

    for (Triangle& triangle: triangles_)
    {
        triangle.foreach_point([&](Vector2D* vertex, unsigned int index) {
            if (*vertex == v1)
            {
                triangles.push_back(triangle);
            }
        });
    }

    return triangles;
}

void MyPolygon::check_delaunay()
{
    auto t = triangles_.begin();

    while (t != triangles_.end())
    {
        t->check_delaunay(points_to_build_polygon_);
        t++;
    }
}



























//void MyPolygon::delaunay_triangulation(std::vector<Vector2D>& pointsRelative)
//{
//    vector<Vector2D>::iterator pi = pointsRelative.begin() + 3;
//
//    while (pi != pointsRelative.end())
//    {
//        // Extract top and top_1.
//        top = CHstack.top();
//        CHstack.pop();
//        top_1 = CHstack.top();
//        CHstack.push(top);
//
//        while (!is_on_the_left(&(*pi), top_1, top))
//        {
//            CHstack.pop();
//
//             Update values of top and top_1.
//            top = CHstack.top();
//            CHstack.pop();
//            top_1 = CHstack.top();
//            CHstack.push(top);
//        }
//
//        CHstack.push(&(*pi));
//        pi++;
//    }
//
//     Get stack points to create current polygon.
//    current_n_ = CHstack.size();
//    n_max_ = current_n_;
//    tab_pts_ = new Vector2D[n_max_ + 1];
//
//    int i = current_n_ - 1;
//
//    while (!CHstack.empty())
//    {
//        tab_pts_[i--] = *(CHstack.top()) + origin; // Place the popped point in the global referential.
//        CHstack.pop();
//    }
//
//    tab_pts_[current_n_] = tab_pts_[0];
//}

//void MyPolygon::check_delaunay()
//{
//    auto t = triangles_.begin();
//
//    while (t != triangles_.end())
//    {
//        t->check_delaunay(tab_pts_);
//        t++;
//    }
//}