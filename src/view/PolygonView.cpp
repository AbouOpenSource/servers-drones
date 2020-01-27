//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#include "PolygonView.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../controller/ServerController.hpp"

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
    polygon_->solve_delaunay();
    polygon_->check_delaunay();

    for (auto& triangle: polygon_->triangles_)
    {
        triangle.draw();
    }

    // Draw the number of points.
    glLineWidth(1);
    for (int i = 0; i < polygon_->current_n_; i++)
    {
        glBegin(GL_LINES);
        glVertex2f(polygon_->tab_pts_[i].x_ - 10, polygon_->tab_pts_[i].y_ - 10);
        glVertex2f(polygon_->tab_pts_[i].x_ + 10, polygon_->tab_pts_[i].y_ + 10);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(polygon_->tab_pts_[i].x_ + 10, polygon_->tab_pts_[i].y_ - 10);
        glVertex2f(polygon_->tab_pts_[i].x_ - 10, polygon_->tab_pts_[i].y_ + 10);
        glEnd();

        GlutWindow::drawText(polygon_->tab_pts_[i].x_ - 10, polygon_->tab_pts_[i].y_, to_string(i), GlutWindow::ALIGN_RIGHT);
    }

    // TODO
    for (Vector2D points: polygon_->get_points_to_build_polygon())
    {
        glColor3fv(RED);
        GlutWindow::fillEllipse(points.x_, points.y_, 2.5, 2.5);
    }
}

void PolygonView::quit()
{
    View::quit();
}
