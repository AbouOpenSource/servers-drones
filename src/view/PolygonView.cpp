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
    glDisable(GL_TEXTURE_2D);

//    std::cout << "SERVER ADDRESS: " << server_ << std::endl;
//    glColor3fv(draw_helper->get_color(server_->get_color()));

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
}

void PolygonView::quit()
{
    View::quit();
}
//