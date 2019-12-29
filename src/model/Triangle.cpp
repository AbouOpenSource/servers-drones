#include "Triangle.hpp"

Triangle::Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3): circum_center_({0, 0})
// TODO: Give a value for circum_center_ initialisation
{
    ptr_[0] = ptr1;
    ptr_[1] = ptr2;
    ptr_[2] = ptr3;

    is_highlighted_ = false;

    calculate_circle();
}

void Triangle::update_vertices(Vector2D *ptr1, Vector2D *ptr2, Vector2D *ptr3)
{
    ptr_[0] = ptr1;
    ptr_[1] = ptr2;
    ptr_[2] = ptr3;

    is_highlighted_ = false;

    calculate_circle();
}

void Triangle::calculate_circle()
{
    // calculate circle parameters
    // ab = b - a
    Vector2D ab = *ptr_[1] - *ptr_[0];
    Vector2D ac = *ptr_[2] - *ptr_[0];
    Vector2D vac = ac.ortho();
    float k = (ab * ab - ac * ab) / (2 * (vac * ab));

    circum_center_ = 0.5f * ac + (k * vac) + *ptr_[0]; // O + 0.5AC + K * vac + A
    circum_radius_ = (circum_center_ - *ptr_[0]).norm(); // R = AO = BO = CO
}


void Triangle::on_mouse_move(const Vector2D& pos)
{
    is_highlighted_ = is_inside(pos);
}

bool Triangle::is_on_the_left(const Vector2D *P, const Vector2D *P1, const Vector2D *P2)
{
    Vector2D ab = *P2 - *P1, ap = *P - *P1;

    return (ab.x_ * ap.y_ - ab.y_ * ap.x_) >= 0;
}

bool Triangle::is_empty(const std::vector<Vector2D*> &tmp, int n)
{
    auto p = tmp.begin() + n;

    while (p!=tmp.end()
        && (!is_on_the_left(*p, ptr_[0], ptr_[1])
        || !is_on_the_left(*p, ptr_[1], ptr_[2])
        || !is_on_the_left(*p, ptr_[2], ptr_[0])))
    {
        p++;
    }

    return p == tmp.end();
}

bool Triangle::is_inside(const Vector2D &p)
{
    return is_on_the_left(&p, ptr_[0], ptr_[1]) && is_on_the_left(&p, ptr_[1], ptr_[2]) && is_on_the_left(&p, ptr_[2], ptr_[0]);
}

bool Triangle::is_inside_circle(const Vector2D &p)
{
    Matrix33 mat33;

    mat33.m[0][0] = ptr_[0]->x_ - p.x_;
    mat33.m[0][1] = ptr_[0]->y_ - p.y_;
    mat33.m[0][2] = ((ptr_[0]->x_ * ptr_[0]->x_) - (p.x_ * p.x_)) + ((ptr_[0])->y_ * ptr_[0]->y_) - (p.y_ * p.y_);

    mat33.m[1][0] = ptr_[1]->x_ - p.x_;
    mat33.m[1][1] = ptr_[1]->y_ - p.y_;
    mat33.m[1][2] = ((ptr_[1]->x_ * ptr_[1]->x_) - (p.x_ * p.x_)) + ((ptr_[1]->y_ * ptr_[1]->y_) - (p.y_ * p.y_));

    mat33.m[2][0] = ptr_[2]->x_ - p.x_;
    mat33.m[2][1] = ptr_[2]->y_ - p.y_;
    mat33.m[2][2] = ((ptr_[2]->x_ * ptr_[2]->x_) - (p.x_ * p.x_)) + ((ptr_[2]->y_ * ptr_[2]->y_) - (p.y_ * p.y_));

    return mat33.determinant() > 0;
}

bool Triangle::check_delaunay(const std::vector<Vector2D> &points) {
    auto p = points.begin();

    while(p != points.end() && !is_inside_circle(*p))
    {
        p++;
    }

    is_delaunay_ = p == points.end();
    return is_delaunay_;
}

void Triangle::draw() {
    glColor3fv(is_delaunay_ ? (is_highlighted_ ? GREEN : GREY) : (is_highlighted_ ? ORANGE : YELLOW));

    // Draw the triangle.
    glBegin(GL_TRIANGLES);
    glVertex2f(ptr_[0]->x_, ptr_[0]->y_);
    glVertex2f(ptr_[1]->x_, ptr_[1]->y_);
    glVertex2f(ptr_[2]->x_, ptr_[2]->y_);
    glEnd();

    // Draw the borders.
    glColor3fv(BLACK);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ptr_[0]->x_, ptr_[0]->y_);
    glVertex2f(ptr_[1]->x_, ptr_[1]->y_);
    glVertex2f(ptr_[2]->x_, ptr_[2]->y_);
    glEnd();
}

void Triangle::draw_circle() {
    // draw circle
    if (is_highlighted_)
    {
        glColor3fv(RED);
        glPushMatrix();
        glTranslatef(circum_center_.x_, circum_center_.y_, 0);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);

        float a=0.0;

        for (int i=0; i<40; i++)
        {
            glVertex2f(circum_radius_ * cos(a), circum_radius_ * sin(a));
            a+=(float)(M_PI/20.0);
        }

        glEnd();
        glLineWidth(1);
        glPopMatrix();
    }
}