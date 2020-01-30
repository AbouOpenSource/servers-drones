//
// Created by abou on 22/01/2020.
//

#include "DroneView.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneChangeZoneEvent.hpp"

DroneView::DroneView(Drone *drone): TextureView("drone"), drone_(drone)
{}

void DroneView::init(View::DrawHelper *draw_helper, EventManager *event_manager)
{
    TextureView::init(draw_helper, event_manager);
    event_manager->subscribe(EventType::DRONE_CHANGED_ZONE, [this] (Event* e, auto&) {
        auto* event = (DroneChangeZoneEvent*)e;
        if (event->get_drone() == drone_) {
            server_ = event->get_server();
        }
    });
}

void DroneView::start()
{
    glClearColor(1.0,1.0,1.0,1.0); // background color
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void DroneView::draw(DrawHelper* draw_helper)
{
    auto& position = drone_->get_position();

    glDisable(GL_TEXTURE_2D);

    if (server_) {
        glBegin(GL_LINES);
        glLineWidth(0.1);
        glVertex2f(position.x_, position.y_);
        glVertex2f(server_->get_position().x_, server_->get_position().y_);
        glEnd();
    }

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glPushMatrix();
    glTranslatef(position.x_ ICON_MARGIN, position.y_ ICON_MARGIN, 1.0);

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
}
