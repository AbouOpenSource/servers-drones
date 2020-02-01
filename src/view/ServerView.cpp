//
// Created by abou on 22/01/2020.
//

#include "ServerView.hpp"
#include "../core/event/internal/EventType.hpp"

ServerView::ServerView(Server *server)
    : TextureView("master"),
    server_(server)
{}

void ServerView::init(View::DrawHelper *draw_helper, ServiceContainer *service_container)
{
    TextureView::init(draw_helper, service_container);
    diagram_controller_ = (DiagramController*)service_container->get_service(DiagramController::SERVICE);
    zone_controller_ = (ZoneController*)service_container->get_service(ZoneController::SERVICE);
}

void ServerView::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ServerView::draw(DrawHelper* draw_helper)
{
    auto& x = server_->get_position().x_;
    auto& y = server_->get_position().y_;

    if (server_->is_selected()) {
        int triangle_amount = 1000;
        GLfloat twice_pi = 2.0f * M_PI;

        glEnable(GL_LINE_SMOOTH);
        glLineWidth(5.0);

        glBegin(GL_LINES);
        glColor4fv(WHITE);
        for(int i = 0; i <= triangle_amount; i++)
        {
            glVertex2f( x, y);
            glVertex2f(
                    x + (ICON_SELECTION_CIRCLE_RADIUS * cos(i * twice_pi / triangle_amount)),
                    y + (ICON_SELECTION_CIRCLE_RADIUS * sin(i * twice_pi / triangle_amount))
            );
        }
        glEnd();
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glPushMatrix();
    glTranslatef(x ICON_MARGIN, y ICON_MARGIN, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0,0.0);
    glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0);
    glVertex2f(ICON_SIZE,0.0);
    glTexCoord2f(1.0,1.0);
    glVertex2f(ICON_SIZE, ICON_SIZE);
    glTexCoord2f(0.0,1.0);
    glVertex2f(0.0, ICON_SIZE);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glColor3fv(BLACK);

    float area = std::roundf(diagram_controller_->get_server_area(server_) * 100);
    std::string area_string = std::to_string(area);
    area_string = area_string.substr(0, area_string.find('.')+3);
    
    auto* data = zone_controller_->get_server_data(server_);

    int left_padding = x + (ICON_SIZE / 2) + 6;

    draw_helper->write_text("Name: " + server_->get_name(), left_padding, y + 12);
    draw_helper->write_text("Area: " + area_string + "%", left_padding, y + 2);
    draw_helper->write_text("Neighbors: " + std::to_string(data->neighbors.size()), left_padding, y - 8);
    draw_helper->write_text("Count: " + std::to_string(data->drones.size()) + '/' + std::to_string((int)data->expected), left_padding, y - 18);
}

