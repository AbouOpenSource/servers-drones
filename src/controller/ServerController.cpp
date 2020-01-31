//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include <array>
#include "ServerController.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/io/reader/FileStream.hpp"
#include "../util/StringUtil.hpp"
#include "../util/VectorUtil.hpp"
#include "../model/Circle.hpp"
#include "../core/event/internal/ServerConfigChangeEvent.hpp"
#include "../core/event/internal/ConfigSaveEvent.hpp"
#include "../core/event/internal/SelectionDeleteEvent.hpp"
#include "../core/event/internal/SelectionClearEvent.hpp"
#include "../core/event/internal/SelectionColorChangeEvent.hpp"
#include "../core/event/internal/AddServerEvent.hpp"
#include "../core/event/internal/AddDroneEvent.hpp"
#include "../core/event/internal/KeyPressEvent.hpp"
#include "../core/event/internal/MouseClickEvent.hpp"
#include "../core/event/internal/DroneConfigChangeEvent.hpp"
#include "../core/event/internal/EventType.hpp"
#include "../core/event/internal/DroneChangeZoneEvent.hpp"

std::string ServerController::SERVICE = "ServerService";

ServerController::ServerController()
    : Controller(ServerController::SERVICE),
    servers_({}),
    server_view_({}),
    drone_view_({}),
    server_drones_({}),
    drone_id_incrementer_(0),
    window_((Window *) get_service(Window::SERVICE))
{
    event_manager_->subscribe({EventType::KEY_PRESSED, EventType::MOUSE_CLICKED, EventType::MOUSE_MOVED},
            [this] (Event* e, const EventManager::EventDetail& detail) {
                on_input(detail.type, e);
            }
    );

    event_manager_->subscribe(EventType::DIAGRAM_CHANGED, [this] (Event* e, auto) {
        for (auto& server_view: server_view_) {
            window_->addView(server_view.second);
        }
    });

    event_manager_->subscribe(EventType::DRONE_CHANGED_ZONE, [this] (Event* e, auto) {
        auto* event = (DroneChangeZoneEvent*)e;
        attach_drone_to_server(event->get_drone(), event->get_server());
    });
}

Server* ServerController::create_server(const std::string& name, const std::string& color, int x, int y)
{
    auto* server = new Server(name, color);
    auto* server_view = new ServerView(server);

    server->get_position().x_ = x;
    server->get_position().y_ = y;

    servers_.push_back(server);
    server_view_[server] = server_view;
    server_drones_[server] = {};

    event_manager_->publish(EventType::SERVER_ADDED, new AddServerEvent(server));

    return server;
}

Server* ServerController::find_server_by_name(const std::string& server_name)
{
    for (Server* server: servers_) {
        if (server->get_name() == server_name) {
            return server;
        }
    }

    return nullptr;
}

Server *ServerController::get_server_at(Position position)
{
    Circle zone(position, ICON_SELECTION_RADIUS);

    for (Server* server: servers_) {
        Position server_position(server->get_position().x_, server->get_position().y_);
        Circle server_zone(server_position, ICON_SELECTION_RADIUS);
        if (zone.touch_with(&server_zone)) {
            return server;
        }
    }

    return nullptr;
}

void ServerController::delete_server(Server *server)
{
    // Remove the view
    window_->removeView(server_view_[server]);

    auto view_it = server_view_.find(server);
    if (view_it != server_view_.end()) {
        server_view_.erase(view_it);
    }

    // Remove the key
    auto key_it = server_drones_.find(server);
    if (key_it != server_drones_.end()) {
        server_drones_.erase(key_it);
    }

    // Remove the object
    VectorUtil::delete_object(servers_, server);
}

Drone* ServerController::create_drone()
{
    auto* drone = new Drone(drone_id_incrementer_);
    auto* drone_view = new DroneView(drone);

    drone_id_incrementer_++;
    drones_.push_back(drone);
    drone_view_[drone] = drone_view;

    window_->addView(drone_view);

    event_manager_->publish(EventType::DRONE_ADDED, new AddDroneEvent(drone));

    return drone;
}

Drone* ServerController::find_drone_by_id(const int drone_id)
{
    for (Drone* drone: drones_) {
        if (drone->get_id() == drone_id) {
            return drone;
        }
    }

    return nullptr;
}

Drone * ServerController::get_drone_at(Position position)
{
    Circle zone(position, ICON_SELECTION_RADIUS);
    
    for (Drone* drone: drones_) {
        Position drone_position(drone->get_position().x_, drone->get_position().y_);
        Circle drone_zone(drone_position, ICON_SELECTION_RADIUS);
        if (zone.touch_with(&drone_zone)) {
            return drone;
        }
    }

    return nullptr;
}

void ServerController::delete_drone(Drone *drone)
{
    // Remove the view
    window_->removeView(drone_view_[drone]);

    auto view_it = drone_view_.find(drone);
    if (view_it != drone_view_.end()) {
        drone_view_.erase(view_it);
    }

    // Remove the drone from the associated server list
    detach_drone_from_server(drone);

    // Remove the object
    VectorUtil::delete_object(drones_, drone);
}

std::vector<Server *> ServerController::get_selection()
{
    std::vector<Server*> selection = {};

    for (Server* server: servers_) {
        if (server->is_selected()) {
            selection.push_back(server);
        }
    }

    return selection;
}

void ServerController::delete_selection()
{
    auto selection = get_selection();

    for (Server* server: selection) {
        delete_server(server);
    }

    event_manager_->publish(EventType::SELECTION_DELETED, new SelectionDeleteEvent(selection));
    event_manager_->publish(EventType::SERVER_CONFIG_CHANGED, new ServerConfigChangeEvent(servers_));
}

void ServerController::color_selection(const std::string& color)
{
    auto selection = get_selection();

    for (Server* server: selection) {
        server->set_color(color);
    }

    event_manager_->publish(EventType::SELECTION_COLOR_CHANGED, new SelectionColorChangeEvent(selection, color));
}

void ServerController::clear_selection()
{
    auto selection = get_selection();

    for (Server* server: selection) {
        server->set_selected(false);
    }

    event_manager_->publish(EventType::SELECTION_CLEARED, new SelectionClearEvent(selection));
}

void ServerController::attach_drone_to_server(Drone *drone, Server *server)
{
    if (drone->get_server_name() == server->get_name()) {
        return;
    }

    detach_drone_from_server(drone);

    drone->set_server_name(server->get_name());
    auto& server_drones = server_drones_[server];
    server_drones.push_back(drone);
}

void ServerController::detach_drone_from_server(Drone *drone)
{
    if (drone->get_server_name().empty()) {
        return;
    }

    Server* server = find_server_by_name(drone->get_server_name());
    if (server) {
        auto& server_drones = server_drones_[server];
        VectorUtil::delete_object(server_drones, drone);
    }

    drone->set_server_name("");
}

int ServerController::get_server_attached_drone_count(Server *server)
{
    return server_drones_[server].size();
}

std::string ServerController::get_config_file()
{
    ServiceContainer* service_container = ServiceContainer::get_instance();
    auto* commands = (CommandContainer*) service_container->get_service(CommandContainer::SERVICE);
    return commands->get_value("c");
}

void ServerController::load_last_state(const TypeUtil::Callback& on_loaded)
{
    std::string config_file = ServerController::get_config_file();
    FileStream in_stream(config_file, {";", true});

    std::array<std::string, 3> values;

    servers_.clear();

    in_stream.reader().read([this, &values] (const unsigned int row, const unsigned int col, const std::string& value) {
        values[col] = value;

        if (col == 2) {
            if (values[1].front() == '(' && values[1].back() == ')') {
                values[1].erase(values[1].begin());
                values[1].erase(values[1].end() - 1);

                std::vector<std::string> position = StringUtil::split(values[1], ',');

                std::string name = values[0];
                std::string color = values[2];

                string x_string = StringUtil::trim(position[0]);
                auto x = VectorUtil::string_cast_to<float>(x_string);
                auto y = VectorUtil::string_cast_to<float>(position[1]);

                create_server(name, color, x, y);
            }
        }
    }, [this, &on_loaded] () {
        event_manager_->publish(EventType::CONFIG_LOADED, new ServerConfigChangeEvent(servers_));
        if (on_loaded) {
            on_loaded();
        }
    });
}

void ServerController::save_current_state(const TypeUtil::Callback& on_finish)
{
    std::string config_file = ServerController::get_config_file();
    FileStream out_stream(config_file, {";", true});

    auto writer = out_stream.writer();

    int i(0);
    for (Server* server: servers_) {
        std::string pos = "(" + to_string((int)server->get_position().x_) + "," + to_string((int)server->get_position().y_) + ")";
        writer.write(i, 0, server->get_name());
        writer.write(i, 1, pos);
        writer.write(i, 2, server->get_color());
        i++;
    }

    writer.persist([this, &on_finish] () {
        event_manager_->publish(EventType::CONFIG_SAVED, new ConfigSaveEvent());
        if (on_finish) {
            on_finish();
        }
    });
}

std::vector<Server *>& ServerController::servers()
{
    return servers_;
}

std::vector<Drone*>& ServerController::drones()
{
    return drones_;
}

std::string ServerController::get_next_color()
{
    std::vector<std::string> all_colors = View::DrawHelper::COLORS;
    std::vector<std::string> used_colors;
    std::vector<std::string> available_colors;

    for (Server* server: servers_) {
        used_colors.push_back(server->get_color());
    }

    bool found;
    for (auto& c1: all_colors) {
        found = false;
        for (auto& c2: used_colors) {
            if (c1 == c2) {
                found = true;
                break;
            }
        }
        if (!found) {
            available_colors.push_back(c1);
        }
    }

    if (available_colors.empty()) {
        available_colors = all_colors;
    }

    return available_colors[std::rand() % available_colors.size()];
}

void ServerController::on_input(const char* type, Event *event)
{
    if (type == EventType::KEY_PRESSED) {

        auto* e = (KeyPressEvent*)event;

        switch (e->get_key()) {
            case Window::ENTER:
            case Window::D:
                create_drone();
                event_manager_->publish(EventType::DRONE_CONFIG_CHANGED, new DroneConfigChangeEvent(drones()));
                break;
            case Window::F1:
                color_selection("RED");
                break;
            case Window::F2:
                color_selection("BLACK");
                break;
            case Window::F3:
                color_selection("CYAN");
                break;
            case Window::F4:
                color_selection("YELLOW");
                break;
            case Window::F5:
                color_selection("GREY");
                break;
            case Window::F6:
                color_selection("BLUE");
                break;
            case Window::F7:
                color_selection("ORANGE");
                break;
            case Window::F8:
                color_selection("PINK");
                break;
            case Window::F9:
                color_selection("GREEN");
                break;
            case Window::S:
                save_current_state();
                break;
            case Window::DEL:
                delete_selection();
                break;
        }
    } else if (type == EventType::MOUSE_CLICKED) {

        auto* e = (MouseClickEvent*)event;

        const auto& click = e->get_mouse_click();
        auto& position = e->get_mouse_position();

        if (click == Window::LEFT) {
            if (Server* server = get_server_at({position.X, position.Y})) {
                server->set_selected(!server->is_selected());
            } else if (Drone* drone = get_drone_at({position.X, position.Y})) {
                // TODO : What on left click on a drone ?
            } else {
                clear_selection();
            }
        } else if (click == Window::RIGHT) {
            if (Server* server = get_server_at({position.X, position.Y})) {
                server->set_color(get_next_color());
            } else if (Drone* drone = get_drone_at({position.X, position.Y})) {
                delete_drone(drone);
                event_manager_->publish(EventType::DRONE_CONFIG_CHANGED, new DroneConfigChangeEvent(drones()));
            } else {
                create_server("Test", get_next_color(), position.X, position.Y);
                event_manager_->publish(EventType::SERVER_CONFIG_CHANGED, new ServerConfigChangeEvent(servers()));
            }
        }
    }
}