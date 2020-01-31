//
// Created by Maanrifa Bacar Ali on 23/01/2020.
//

#include "PolygonView.hpp"

PolygonView::PolygonView(Polygon *polygon, Server* server): View(), polygon_(polygon), server_(server)
{}

void PolygonView::init(DrawHelper* draw_helper, EventManager* event_manager)
{
    View::init(draw_helper, event_manager);
}

void PolygonView::start()
{
    View::start();
}

void PolygonView::draw(View::DrawHelper *draw_helper)
{
    // Draw Voronoi Diagram.
    glDisable(GL_TEXTURE_2D);

    glColor3fv(draw_helper->parse(server_->get_color()));
    //glColor3fv(draw_helper->dynamic_color());

    glBegin(GL_POLYGON);
    for (auto &point: polygon_->get_build_points()) {
        glVertex2f(point.x_, point.y_);
    }
    glEnd();

    glColor3fv(BLACK);
    for (auto &point: polygon_->get_build_points()) {
        Vector2D *next_point = polygon_->next_vertex(point);

        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(point.x_, point.y_);
        glVertex2f(next_point->x_, next_point->y_);
        glEnd();
    }

    /*
    // Draw polygon triangulation (not working anymore).
    for (auto& triangle: polygon_->get_triangles())
    {
        triangle.draw();
    }

    // Draw the number of points.
    glLineWidth(1);
    for (int i = 0; i < sizeof(polygon_->get_tab_pts()); i++)
    {
        glBegin(GL_LINES);
        glVertex2f(polygon_->get_tab_pts()[i].x_ - 10, polygon_->get_tab_pts()[i].y_ - 10);
        glVertex2f(polygon_->get_tab_pts()[i].x_ + 10, polygon_->get_tab_pts()[i].y_ + 10);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(polygon_->get_tab_pts()[i].x_ + 10, polygon_->get_tab_pts()[i].y_ - 10);
        glVertex2f(polygon_->get_tab_pts()[i].x_ - 10, polygon_->get_tab_pts()[i].y_ + 10);
        glEnd();

        GlutWindow::drawText(polygon_->get_tab_pts()[i].x_ - 10, polygon_->get_tab_pts()[i].y_, to_string(i), GlutWindow::ALIGN_RIGHT);
    }

    for (Vector2D points: polygon_->get_build_points())
    {
        glColor3fv(RED);
        GlutWindow::fillEllipse(points.x_, points.y_, 2.5, 2.5);
    }
     */
}

void PolygonView::quit()
{
    View::quit();
}
