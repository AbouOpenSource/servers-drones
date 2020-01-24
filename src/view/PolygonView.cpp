//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#include "PolygonView.hpp"

PolygonView::PolygonView(Polygon *polygon): View(), polygon_(polygon)
{}

void PolygonView::init(InputManager *input_manager, EventManager *event_manager,
                       const View::TextureLoader &texture_loader)
{
    View::init(input_manager, event_manager, texture_loader);
}

void PolygonView::start()
{
    View::start();
}

void PolygonView::draw(View::DrawHelper *draw_helper)
{
    auto& triangles = polygon_->get_triangles();
    Vector2D* tab_pts = polygon_->get_tab_pts();

    if (triangles.empty()) {
        polygon_->triangulation();
    }

    // Draw the interior.
    glColor3fv(draw_helper->get_color(polygon_->get_color()));

    glBegin(GL_TRIANGLES);
    for (auto t: triangles)
    {
        glVertex2f(t.ptr_[0]->x_, t.ptr_[0]->y_);
        glVertex2f(t.ptr_[1]->x_, t.ptr_[1]->y_);
        glVertex2f(t.ptr_[2]->x_, t.ptr_[2]->y_);
    }
    glEnd();

    // Draw the border
    glColor3fv(draw_helper->black());
    glLineWidth(3);

    // Draw the triangles.
    glBegin(GL_LINE_LOOP);
    for (const auto& t: triangles)
    {
        glVertex2f(t.ptr_[0]->x_, t.ptr_[0]->y_);
        glVertex2f(t.ptr_[1]->x_, t.ptr_[1]->y_);
        glVertex2f(t.ptr_[2]->x_, t.ptr_[2]->y_);
    }
    for (int i = 0; i < polygon_->get_current_n(); i++)
    {
        glVertex2f(tab_pts[i].x_, tab_pts[i].y_);
    }
    glEnd();

    // Draw the number of points.
    glLineWidth(1);
    for (int i = 0; i < polygon_->get_current_n(); i++)
    {
        glBegin(GL_LINES);
        glVertex2f(tab_pts[i].x_ - 10, tab_pts[i].y_ - 10);
        glVertex2f(tab_pts[i].x_ + 10, tab_pts[i].y_ + 10);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(tab_pts[i].x_ + 10, tab_pts[i].y_ - 10);
        glVertex2f(tab_pts[i].x_ - 10, tab_pts[i].y_ + 10);
        glEnd();

        GlutWindow::drawText(tab_pts[i].x_ - 10, tab_pts[i].y_, to_string(i), GlutWindow::ALIGN_RIGHT);
    }

    auto build_points = polygon_->get_build_points();
    // TODO
    for (const Vector2D& points: build_points)
    {
        glColor3fv(draw_helper->red());
        GlutWindow::fillEllipse(points.x_, points.y_, 2.5, 2.5);
    }
}

void PolygonView::quit()
{
    View::quit();
}
