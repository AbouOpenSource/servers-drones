//
// Created by Maanrifa Bacar Ali on 27/01/2020.
//

#include "TriangleView.hpp"

TriangleView::TriangleView(Triangle *triangle)
    : triangle_(triangle)
{}

void TriangleView::init(View::DrawHelper *draw_helper, EventManager *event_manager)
{
    View::init(draw_helper, event_manager);
}

void TriangleView::start()
{
    View::start();
}

void TriangleView::draw(View::DrawHelper *draw_helper)
{
    View::draw(draw_helper);

    glColor3fv(triangle_->is_delaunay()
    ? (triangle_->is_highlighted() ? GREEN : GREY)
    : (triangle_->is_highlighted() ? ORANGE : YELLOW));

    // Draw the triangle.
    glBegin(GL_TRIANGLES);
    glVertex2f(triangle_->ptr_[0]->x_, triangle_->ptr_[0]->y_);
    glVertex2f(triangle_->ptr_[1]->x_, triangle_->ptr_[1]->y_);
    glVertex2f(triangle_->ptr_[2]->x_, triangle_->ptr_[2]->y_);
    glEnd();

    // Draw the borders.
    glColor3fv(BLACK);
    glBegin(GL_LINE_LOOP);
    glVertex2f(triangle_->ptr_[0]->x_, triangle_->ptr_[0]->y_);
    glVertex2f(triangle_->ptr_[1]->x_, triangle_->ptr_[1]->y_);
    glVertex2f(triangle_->ptr_[2]->x_, triangle_->ptr_[2]->y_);
    glEnd();
}

void TriangleView::draw_circle()
{
    // draw circle
    if (triangle_->is_highlighted())
    {
        glColor3fv(RED);
        glPushMatrix();
        glTranslatef(triangle_->get_circum_center().x_, triangle_->get_circum_center().y_, 0);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);

        float a = 0.0;

        for (int i = 0; i < 40; i++)
        {
            glVertex2f(triangle_->get_circum_radius() * cos(a), triangle_->get_circum_radius() * sin(a));
            a += (float) (M_PI / 20.0);
        }

        glEnd();
        glLineWidth(1);
        glPopMatrix();
    }
}

void TriangleView::quit()
{
    View::quit();
}