#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../vector2D/Vector2D.hpp"
#include "../matrix/determinant.h"
#include <glutWindow.h>

const float BLACK[4]={0.0, 0.0, 0.0, 1.0f};
const float GREY[4]={0.75f, 0.75f, 0.75f, 1.0f};
const float RED[4]={1.0f, 0.0, 0.0, 1.0f};
const float ORANGE[4]={1.0f, 0.27f, 0.0, 1.0f};
const float YELLOW[4]={1.0f, 1.0f, 0.0, 1.0f};
const float GREEN[4]={0.0, 1.0f, 0.0, 1.0f};
const float BLUE[4]={0.0, 0.0, 1.0f, 1.0f};

class Triangle {
public:
    Vector2D *ptr[3];
    bool is_highlighted_;
    Vector2D circum_center_;
    float circum_radius_;
    bool is_delaunay_;

    Triangle(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3)
    {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        is_highlighted_ = false;
        calculateCircle();
    }

//    bool is_equilateral() {
//        return true;
//    }

    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3)
    {
        ptr[0] = ptr1;
        ptr[1] = ptr2;
        ptr[2] = ptr3;
        is_highlighted_ = false;
        calculateCircle();
    }

    void calculateCircle()
    {
        // calculate circle parameters
        // AB = B - A
        Vector2D AB = *ptr[1] - *ptr[0];
        Vector2D AC = *ptr[2] - *ptr[0];
        Vector2D VAC = AC.ortho();
        float k = (AB * AB - AC * AB) / (2 * (VAC * AB));

        circum_center_ = 0.5f * AC + (k * VAC) + *ptr[0]; // O + 0.5AC + K * VAC + A
        circum_radius_ = (circum_center_ - *ptr[0]).norm(); // R = AO = BO = CO
    }

    void onMouseMove(const Vector2D& pos)
    {
        is_highlighted_ = is_inside(pos);
    }

    bool is_on_the_left(const Vector2D *P, const Vector2D *P1, const Vector2D *P2)
    {
        Vector2D AB = *P2-*P1,
                AP = *P-*P1;

        return (AB.x*AP.y - AB.y*AP.x)>=0;
    }

    bool isEmpty(const std::vector<Vector2D*> &tmp,int n)
    {
        auto p = tmp.begin() + n;
        
        while (p!=tmp.end() && (!is_on_the_left(*p, ptr[0], ptr[1]) || !is_on_the_left(*p, ptr[1], ptr[2]) || !is_on_the_left(*p,
                                                                                                                              ptr[2],
                                                                                                                              ptr[0]))) {
            p++;
        }
        
        return p == tmp.end();
    }

    bool is_inside(const Vector2D &P)
    {
        return is_on_the_left(&P, ptr[0], ptr[1]) && is_on_the_left(&P, ptr[1], ptr[2]) && is_on_the_left(&P, ptr[2], ptr[0]);
    }

    bool is_inside_circle(const Vector2D &P)
    {
        Matrix33 mat33;

        mat33.m[0][0] = ptr[0]->x - P.x;
        mat33.m[0][1] = ptr[0]->y - P.y;
        mat33.m[0][2] = ((ptr[0]->x * ptr[0]->x) - (P.x * P.x)) + ((ptr[0])->y * ptr[0]->y) - (P.y * P.y);

        mat33.m[1][0] = ptr[1]->x - P.x;
        mat33.m[1][1] = ptr[1]->y - P.y;
        mat33.m[1][2] = ((ptr[1]->x * ptr[1]->x) - (P.x * P.x)) + ((ptr[1]->y * ptr[1]->y) - (P.y * P.y));

        mat33.m[2][0] = ptr[2]->x - P.x;
        mat33.m[2][1] = ptr[2]->y - P.y;
        mat33.m[2][2] = ((ptr[2]->x * ptr[2]->x) - (P.x * P.x)) + ((ptr[2]->y * ptr[2]->y) - (P.y * P.y));

        return mat33.determinant() > 0;
    }

    bool check_delaunay(const vector<Vector2D> &points) {
        auto p = points.begin();

        while(p != points.end() && !is_inside_circle(*p))
        {
            p++;
        }

        is_delaunay_ = p == points.end();
        return is_delaunay_;
    }

    void draw() {
        glColor3fv(is_delaunay_ ? (is_highlighted_ ? GREEN : GREY) : (is_highlighted_ ? ORANGE : YELLOW));

        // Draw the triangle.
        glBegin(GL_TRIANGLES);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();

        // Draw the borders.
        glColor3fv(BLACK);
        glBegin(GL_LINE_LOOP);
        glVertex2f(ptr[0]->x,ptr[0]->y);
        glVertex2f(ptr[1]->x,ptr[1]->y);
        glVertex2f(ptr[2]->x,ptr[2]->y);
        glEnd();
    }

    void drawCircle() {
        // draw circle
        if (is_highlighted_) {
            glColor3fv(RED);
            glPushMatrix();
            glTranslatef(circum_center_.x, circum_center_.y, 0);
            glLineWidth(3);
            glBegin(GL_LINE_LOOP);
            float a=0.0;
            for (int i=0; i<40; i++) {
                glVertex2f(circum_radius_ * cos(a), circum_radius_ * sin(a));
                a+=(float)(M_PI/20.0);
            }
            glEnd();
            glLineWidth(1);
            glPopMatrix();
        }
    }
};

#endif //TRIANGLE_H
