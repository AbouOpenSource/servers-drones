#include <stack>
#include <algorithm>
#include <cstring>
#include "Polygon.hpp"
#include "../util/VectorUtil.hpp"

Polygon::Polygon(): tab_pts_(new Vector2D[0]), n_max_(0), current_n_(0)
{}

Polygon::Polygon(int p_max): tab_pts_{new Vector2D[p_max]}, n_max_{p_max}, current_n_{0}
{}

void Polygon::init(std::vector<Server>& servers)
{
    std::vector<Vector2D> points;

    for (const Server& server: servers) {
        points.push_back(server.get_position());
    }

//    std::cout << "\n";
//    VectorUtil::print_1D_vector(points);

//    assert(points.size() > 3);
    build_points = points;

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
    if (pymin != points.begin()) {
        iter_swap(points.begin(), pymin);
    }

    Vector2D origin{points.begin()->x_, points.begin()->y_};

    // Copy points in a set of points relative to points[0]
    vector<Vector2D> pointsRelative;

    for (auto pOrig: points) {
        pointsRelative.push_back(Vector2D{pOrig.x_ - origin.x_, pOrig.y_ - origin.y_});
    }

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

Polygon::~Polygon()
{
    delete [] tab_pts_;
}

int Polygon::get_n_max() const
{
    return n_max_;
}

int Polygon::get_current_n() const
{
    return current_n_;
}

const std::string Polygon::get_color() const
{
    return color_;
}

Vector2D *Polygon::get_tab_pts() const
{
    return tab_pts_;
}

const vector<Triangle> &Polygon::get_triangles() const
{
    return triangles_;
}

const vector<Vector2D> &Polygon::get_interior_points() const
{
    return interior_points;
}

const vector<Vector2D> &Polygon::get_build_points() const
{
    return build_points;
}

bool Polygon::polar_comparison(Vector2D p1, Vector2D p2)
{
    double a1 = asin(p1.y_ / sqrt(p1.x_ * p1.x_ + p1.y_ * p1.y_));
    if (p1.x_ < 0.0)
        a1 = M_PI - a1;

    double a2 = asin(p2.y_ / sqrt(p2.x_ * p2.x_ + p2.y_ * p2.y_));
    if (p2.x_ < 0.0)
        a2 = M_PI - a2;

    return a1 < a2;
}

bool Polygon::is_on_the_left(const Vector2D& p, int i)
{
    Vector2D ab = tab_pts_[i + 1] - tab_pts_[i],
            ap = p - tab_pts_[i];

    return cross_product(ab, ap) >= 0;
}

bool Polygon::is_on_the_left(const Vector2D* p, const Vector2D* p1, const Vector2D* p2)
{
    Vector2D ab = *p2 - *p1,
            ap = *p - *p1;

    return cross_product(ab, ap) >= 0;
//    (ab.x_ * ap.y_ - ab.y_ * ap.x_) >= 0;
}

bool Polygon::is_convex()
{
    unsigned int i = 0;

    while (i < current_n_ && is_on_the_left(tab_pts_[(i + 2) % current_n_], i))
        i++;

    return i == current_n_;
}

bool Polygon::add_vertex(const Vector2D &p)
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
bool Polygon::is_inside(const Vector2D& p)
{
    int i = 0;
    while (i < current_n_ && is_on_the_left(p, i))
        i++;

    return i == current_n_;
}

bool Polygon::is_inside_triangle(const Vector2D& p)
{
    auto triangle = triangles_.begin();

    while (triangle != triangles_.end() && !(*triangle).is_inside(p))
        triangle++;

    return triangle != triangles_.end();
}

void Polygon::set_color(const std::string& color)
{
    color_ = color;
}

vector<float> Polygon::intersect(const Vector2D& a, const Vector2D& u, const Vector2D& p, const Vector2D& q)
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

std::vector<float> Polygon::intersections(const Vector2D& a, const Vector2D& u)
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

void Polygon::triangulation()
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

    /********** Interior point triangles **********/
    for (Vector2D interior_point: interior_points)
    {
//        std::cout << interior_point << "\n";

        auto it_triangle = triangles_.begin();

        while (it_triangle != triangles_.end())
        {
            if (it_triangle->is_inside(interior_point))
            {
                const Triangle triangle = *it_triangle;
                Vector2D p1_triangle = *(triangle.ptr_[0]);
                Vector2D p2_triangle = *(triangle.ptr_[1]);
                Vector2D p3_triangle = *(triangle.ptr_[2]);

//                std::cout << "before erase: " << triangles_.size() << "\n";
//                it_triangle = triangles_.erase(it_triangle);
//                std::cout << "after erase: " << triangles_.size() << "\n";

                Triangle triangle1 = Triangle(&p1_triangle, &p2_triangle, &interior_point);
                Triangle triangle2 = Triangle(&p2_triangle, &p3_triangle, &interior_point);
                Triangle triangle3 = Triangle(&p3_triangle, &p1_triangle, &interior_point);

//                triangles_.push_back(triangle1);
//                triangles_.push_back(triangle2);
//                triangles_.push_back(triangle3);
            }
//            else
//            {
                ++it_triangle;
//            }
        }
    }
}

float Polygon::cross_product(const Vector2D& u, const Vector2D& v)
{
    return (u.x_ * v.y_ - u.y_ * v.x_);
}

void Polygon::delaunay_triangulation(std::vector<Vector2D> &relative_points)
{

}

void Polygon::delaunay_check()
{

}

//void Polygon::delaunay_triangulation(std::vector<Vector2D>& pointsRelative)
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

//void Polygon::check_delaunay()
//{
//    auto t = triangles_.begin();
//
//    while (t != triangles_.end())
//    {
//        t->check_delaunay(tab_pts_);
//        t++;
//    }
//}