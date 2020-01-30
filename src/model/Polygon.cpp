
#include <stack>
#include <algorithm>
#include <cstring>
#include <list>
#include "Polygon.hpp"
#include "../util/VectorUtil.hpp"

Polygon::Polygon(int max_pts)
    : tab_pts_{new Vector2D[max_pts]},
    n_max_(max_pts),
    current_n_(0),
    build_points_()
{}

Polygon::Polygon(std::vector<Vector2D> points, int max_pts)
    : tab_pts_{new Vector2D[max_pts]},
    n_max_(max_pts),
    current_n_(0),
    build_points_(points)
{}

Polygon::~Polygon()
{
    delete [] tab_pts_;
}

void Polygon::init()
{
    std::vector<Vector2D> points = build_points_;

    auto p = points.begin();
    auto pymin = points.begin();

    // find point with minimal y and swap with first point
    while (p != points.end()) {
        if (p->y_ < pymin->y_) {
            pymin = p;
        }
        p++;
    }

    // Swap
    if (pymin != points.begin()) {
        iter_swap(points.begin(), pymin);
    }

    Vector2D origin{points.begin()->x_, points.begin()->y_};

    // Copy points in a set of points relative to points[0]
    vector<Vector2D> relative_points;

    for (auto pOrig: points) {
        relative_points.push_back(Vector2D{pOrig.x_ - origin.x_, pOrig.y_ - origin.y_});
    }

    // Sorting point with angular criteria.
    sort(relative_points.begin() + 1, relative_points.end(), polar_comparison);

    std::stack<Vector2D*> ch_stack;
    Vector2D *top_1, *top;
    ch_stack.push(&relative_points[0]);
    ch_stack.push(&relative_points[1]);
    ch_stack.push(&relative_points[2]);

    // TODO START DELAUNAY TRIANGULATION.
    vector<Vector2D>::iterator pi = relative_points.begin() + 3;

    while (pi != relative_points.end()) {
        // Extract top and top_1.
        top = ch_stack.top();
        ch_stack.pop();
        top_1 = ch_stack.top();
        ch_stack.push(top);

        while (!is_on_the_left(&(*pi), top_1, top)) {
            // Add interior point
            const Vector2D interior_point(top->x_ + origin.x_, top->y_ + origin.y_);
            interior_points_.push_back(interior_point);

            ch_stack.pop();
            // Update values of top and top_1.
            top = ch_stack.top();
            ch_stack.pop();
            top_1 = ch_stack.top();
            ch_stack.push(top);
        }

        ch_stack.push(&(*pi));
        pi++;
    }

    // Get stack points to create current polygon.
    current_n_ = ch_stack.size();
    n_max_ = current_n_;
    tab_pts_ = new Vector2D[n_max_ + 1];

    std::vector<Vector2D*> test;
    test.resize(n_max_ + 1);

    int i = current_n_ - 1;

    while (!ch_stack.empty()){
        tab_pts_[i--] = *(ch_stack.top()) + origin; // Place the popped point in the global referential.
        ch_stack.pop();
    }

    tab_pts_[current_n_] = tab_pts_[0];
    // TODO END DELAUNAY TRIANGULATION

    triangulation();
    interior_triangulation();
    check_delaunay();
    solve_delaunay();
    check_delaunay();
}

bool Polygon::polar_comparison(Vector2D p1, Vector2D p2)
{
    double a1 = asin(p1.y_ / sqrt(p1.x_ * p1.x_ + p1.y_ * p1.y_));
    if (p1.x_ < 0.0) {
        a1 = M_PI - a1;
    }

    double a2 = asin(p2.y_ / sqrt(p2.x_ * p2.x_ + p2.y_ * p2.y_));
    if (p2.x_ < 0.0) {
        a2 = M_PI - a2;
    }

    return a1 < a2;
}

bool Polygon::is_on_the_left(const Vector2D& p, int i)
{
    Vector2D ab = tab_pts_[i + 1] - tab_pts_[i], ap = p - tab_pts_[i];

    return cross_product(ab, ap) >= 0;
}

bool Polygon::is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2)
{
    Vector2D ab = *p2 - *p1, ap = *p - *p1;

    return cross_product(ab, ap) >= 0;
//    (ab.x_ * ap.y_ - ab.y_ * ap.x_) >= 0;
}

bool Polygon::is_convex()
{
    unsigned int i = 0;

    while (i < current_n_ && is_on_the_left(tab_pts_[(i + 2) % current_n_], i)) {
        i++;
    }

    return i == current_n_;
}

bool Polygon::add_vertex(Vector2D &p)
{
    if (current_n_ == n_max_) {
        return false;
    }

    tab_pts_[current_n_++] = p;
    tab_pts_[current_n_] = tab_pts_[0];

    build_points_.push_back(p);

    return true;
}

// Complexity is N because for each edge and there is N edges.
bool Polygon::is_inside(const Vector2D& p)
{
    return is_inside_left(p) || is_in_side_right(p);
}

bool Polygon::is_inside_left(const Vector2D &p) {
    int i = 0;

    while (i < current_n_ && is_on_the_left(p, i)) {
        i++;
    }

    return i == current_n_;
}

bool Polygon::is_inside_triangle(const Vector2D& p)
{
    auto triangle = triangles_.begin();

    while (triangle != triangles_.end() && !(*triangle).is_inside(p)) {
        triangle++;
    }

    return triangle != triangles_.end();
}

vector<float> Polygon::intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q)
{
    std::vector<float> k;

    Vector2D pq = q - p;
    Vector2D ap = p - a;

    float det = cross_product(u, pq);

    if (det == 0.0) {
        return k;
    }

    k.push_back(cross_product(ap, pq) / det); // k1: am = k1 x u
    k.push_back(cross_product(ap, u) / det); // k2: pm = k2 x pq

    return k;
}

std::vector<float> Polygon::intersections(const Vector2D& a, const Vector2D& u)
{
    std::vector<float> k1k2;
    std::vector<float> kres;

    for (int i = 0; i < current_n_; ++i) {
        k1k2 = intersect(a, u, tab_pts_[i], tab_pts_[i + 1]);

        if (k1k2.size() == 2 && k1k2[1] >= 0.0 && k1k2[1] <= 1.0) {
            auto it = kres.begin();
            auto prev_it = kres.begin();

            while (it != kres.end() && (*it) < k1k2[0]) {
                prev_it = it;
                it++;
            }

            kres.insert(prev_it, k1k2[0]);
        }
    }

    return kres;
}

void Polygon::solve_delaunay()
{
    std::list<Triangle*> process_list;
    auto t = triangles_.begin(); // copy tabTriangles in a list

    while (t != triangles_.end()) {
        process_list.push_back(&(*t));
        t++;
    }

    while (process_list.size() > 1)
    {
        // while a triangle is in the list
        Triangle *current = process_list.front(); // pop current
        process_list.pop_front();

        if (!current->is_delaunay()) {
            // TODO Solve the bug of the infinite loop when we add more servers.

            // if current is not Delaunay.
            Triangle *triangle_neighbor = neighbor_inside(current);

            if (triangle_neighbor != nullptr) {
                // and if a neighbor is available
                flip(current, triangle_neighbor); // flip the common edge

                // remove Tneighbor form the list
                auto tr = process_list.begin();
                while (tr != process_list.end() && (*tr) != triangle_neighbor) {
                    tr++;
                }

                if (tr != process_list.end()) {
                    process_list.erase(tr);
                }
            } else {
                process_list.push_back(current); // postpone the treatment
            }
        }
    }
}

Triangle* Polygon::neighbor_inside(Triangle* current)
{
    // For each triangle.
    for (Triangle &triangle: triangles_) {
        // If the triangle is the one passed in parameter.
        if (&triangle == current) {
            continue;
        }

        int common_points(0);
        bool point_inside_circle(false);

        // For each point of the triangle.
        for (Vector2D* point: triangle.ptr_) {
            // If the point is inside the circumscribe circle of the current triangle.
            if (current->is_inside_circle(*point)) {
                point_inside_circle = true;
            }

            // If the point is a common point with the triangle passed in parameter.
            if (current->common_point(point)) {
                common_points++;
            }
        }

        // Found a triangle.
        if (common_points == 2 && point_inside_circle) {
            return &triangle;
        }
    }

    // No triangle found.
    return nullptr;
}

void Polygon::flip(Triangle* current, Triangle* neighbor)
{
    std::vector<unsigned int> index_common_points_current;
    unsigned int index_no_common_points_current;

    current->foreach_point([&](Vector2D* point, unsigned int index) {
        if (neighbor->common_point(point)) {
            index_common_points_current.push_back(index);
        } else {
            index_no_common_points_current = index;
        }
    });

    std::vector<unsigned int> index_common_points_neighbor;
    unsigned int index_no_common_points_neighbor;

    neighbor->foreach_point([&](Vector2D* point, unsigned int index) {
        if (current->common_point(point)) {
            index_common_points_neighbor.push_back(index);
        } else {
            index_no_common_points_neighbor = index;
        }
    });

    if (current->ptr_[index_common_points_current[0]] == neighbor->ptr_[index_common_points_neighbor[0]]) {
        neighbor->ptr_[index_common_points_neighbor[1]] = current->ptr_[index_no_common_points_current];
    } else {
        neighbor->ptr_[index_common_points_neighbor[0]] = current->ptr_[index_no_common_points_current];
    }

    current->ptr_[index_common_points_current[0]] = neighbor->ptr_[index_no_common_points_neighbor];

    current->calculate_circle();
    neighbor->calculate_circle();
}

void Polygon::triangulation()
{
    std::vector<Vector2D*> tmp;

    // copy the list of vertices in the tmp list.
    for (int i = 0; i < current_n_; i++) {
        tmp.push_back(&(tab_pts_[i]));
    }

    int n = current_n_;

    // while we can add a triangle to tabTriangle.
    while (n > 2) {
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
}

void Polygon::interior_triangulation()
{
    for (Vector2D& interior_point: interior_points_) {
        auto it_triangle = triangles_.begin();

        while (it_triangle != triangles_.end()) {
            if (it_triangle->is_inside(interior_point)) {
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
            } else {
                ++it_triangle;
            }
        }
    }
}

float Polygon::cross_product(const Vector2D& u, const Vector2D& v)
{
    return (u.x_ * v.y_ - u.y_ * v.x_);
}

void Polygon::foreach_vertex(VertexCallback cb)
{
    for (unsigned int i = 0; i < build_points_.size(); i++) {
        cb(build_points_[i], i);
    }
}

std::vector<Triangle> Polygon::get_triangles_from(Vector2D v1)
{
    std::vector<Triangle> triangles;

    for (Triangle& triangle: triangles_) {
        triangle.foreach_point([&](Vector2D* vertex, unsigned int index) {
            if (*vertex == v1) {
                triangles.push_back(triangle);
            }
        });
    }

    return triangles;
}

void Polygon::check_delaunay()
{
    auto t = triangles_.begin();

    while (t != triangles_.end()) {
        t->check_delaunay(build_points_);
        t++;
    }
}

std::ostream &operator<<(std::ostream &out, Polygon &polygon)
{
    out << "Polygon | ";

    polygon.foreach_vertex([&out](Vector2D vertex, unsigned int index) {
        out << vertex << std::endl;
    });

    return out;
}

Vector2D *Polygon::next_vertex(Vector2D &vertex)
{
    Vector2D* next_point(nullptr);

    foreach_vertex([&next_point, &vertex, this](Vector2D& point, unsigned int index) {
        if (point == vertex) {
            next_point = &tab_pts_[(index + 1) % build_points_.size()];
        }
    });

    return next_point;
}

bool Polygon::is_on_the_right(const Vector2D &p, int i) {
    Vector2D u = tab_pts_[i + 1] - tab_pts_[i], v = p - tab_pts_[i];
    return cross_product(u, v) <= 0;
}

bool Polygon::is_in_side_right(const Vector2D &p) {
    int i = 0;

    while (i < current_n_ && is_on_the_right(p, i)) {
        i++;
    }

    return i == current_n_;
}

Vector2D *Polygon::previous_vertex(Vector2D &vertex)
{
    Vector2D* previous_point(nullptr);

    foreach_vertex([&previous_point, &vertex, this](Vector2D& point, unsigned int index) {
        if (point == vertex) {
            if (index == 0) {
                previous_point = &build_points_[build_points_.size()-1];
            } else {
                previous_point = &build_points_[(index - 1)];
            }
        }
    });

    return previous_point;
}

vector<Vector2D> &Polygon::get_build_points()
{
    return build_points_;
}

std::vector<Triangle> &Polygon::get_triangles()
{
    return triangles_;
}

Vector2D *Polygon::get_tab_pts()
{
    return tab_pts_;
}

float Polygon::area()
{
   float area=0.0;
    for (auto p: triangles_) {
        Vector2D AB = *p.ptr_[1] - *p.ptr_[0];
        Vector2D BC = *p.ptr_[2] - *p.ptr_[1];
        Vector2D CA = *p.ptr_[0] - *p.ptr_[2];

        double a = AB.norm();
        double b = BC.norm();
        double c = CA.norm();

        auto s = (a + b + c) / 2;
        auto calculated = std::sqrt(s * (s - a) * (s - b) * (s - c));
        std::cout << calculated << std::endl;
        area += calculated;
    }
    std::cout << "Final Area: " << area << std::endl;


    return area;
}
