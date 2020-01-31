//
// Created by abou on 22/01/2020.
//

#include "ServerView.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DiagramChangeEvent.hpp"

ServerView::ServerView(Server *server): TextureView("master"), server_(server)
{}

void ServerView::init(View::DrawHelper *draw_helper, EventManager *event_manager)
{
    TextureView::init(draw_helper, event_manager);
    /*event_manager->subscribe(EventType::DIAGRAM_CHANGED, [this] (Event* e, auto&) {
        std::cout << ((DiagramChangeEvent*)e)->get_diagram_controller()->get_server_area(server_) << std::endl;
    });*/
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
        int triangleAmount = 1000;
        GLfloat twicePi = 2.0f * M_PI;

        glEnable(GL_LINE_SMOOTH);
        glLineWidth(5.0);

        glBegin(GL_LINES);
        glColor4fv(WHITE);
        for(int i = 0; i <= triangleAmount; i++)
        {
            glVertex2f( x, y);
            glVertex2f(
                    x + (ICON_SELECTION_CIRCLE_RADIUS * cos(i * twicePi / triangleAmount)),
                    y + (ICON_SELECTION_CIRCLE_RADIUS * sin(i * twicePi / triangleAmount))
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

    draw_helper->write_text(server_->get_name(), x + (ICON_SIZE / 2) + 6, y + 5);
    draw_helper->write_text("Area: " + std::to_string(area_ * 100) + "%", x + (ICON_SIZE / 2) + 6, y - 10);
}

