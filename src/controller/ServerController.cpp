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
#include "../core/event/internal/ServerReadyEvent.hpp"
#include "DiagramController.hpp"
#include "../core/event/internal/BackgroundReadyEvent.hpp"
#include "../view/VoronoiDiagramView.hpp"

std::string ServerController::SERVICE = "ServerService";

ServerController::ServerController()
    : ServiceProvider(ServerController::SERVICE),
    servers_({}),
    server_view_({}),
    drone_view_({}),
    server_drone_count_({}),
    drone_id_incrementer_(0)
{
    ServiceContainer* container = ServiceContainer::get_instance();

    event_manager_ = (EventManager *) container->get_service(EventManager::SERVICE);
    window_ = (Window *) container->get_service(Window::SERVICE);
    direction_controller_ = (DirectionController*) ServiceContainer::get_instance()->get_service(DirectionController::SERVICE);
    auto* input_manager = (InputManager *) container->get_service(InputManager::SERVICE);

    input_manager->register_key_press_listener(on_key_pressed());
    input_manager->register_mouse_move_listener(on_mouse_move());
    input_manager->register_mouse_click_listener(on_mouse_click());

    event_manager_->subscribe(EventType::BACKGROUND_READY, on_background_ready());
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

Drone* ServerController::find_drone_by_id(const int drone_id)
{
    for (Drone* drone: drones_) {
        if (drone->get_id() == drone_id) {
            return drone;
        }
    }
    return nullptr;
}

Server * ServerController::get_server_at(Position position)
{
    Circle zone(position, 100);
    for (Server* server: servers_) {
        Position server_position(server->get_position().x_, server->get_position().y_);
        Circle server_zone(server_position, 100);
        if (zone.touch_with(&server_zone)) {
            return server;
        }
    }
    return nullptr;
}

std::vector<Server *> ServerController::get_selected_servers()
{
    std::vector<Server*> selection = {};
    for (Server* server: servers_) {
        if (server->is_selected()) {
            selection.push_back(server);
        }
    }
    return selection;
}

void ServerController::delete_selected_servers()
{
    for (Server* server: servers_) {
        if (server->is_selected()) {
            server->set_selected(false);
        }
    }
}

void ServerController::clear_selection()
{
    for (Server* server: servers_) {
        if (server->is_selected()) {
            server->set_selected(false);
        }
    }
}

void ServerController::set_servers_color(const std::vector<Server *>& servers, const std::string& color)
{
    for (Server* server: servers) {
        server->set_color(color);
    }
}

void ServerController::add_server(Server* server)
{
    auto* server_view = new ServerView(server);
    servers_.push_back(server);
    server_view_[server] = server_view;
    server_drone_count_[server] = 0;
    //window_->addView(server_view);
}

Drone* ServerController::create_drone(Server* server)
{
    auto* drone = new Drone(drone_id_incrementer_);
    auto* drone_view = new DroneView(drone);

    drone_id_incrementer_++;
    drones_.push_back(drone);
    drone_view_[drone] = drone_view;
    window_->addView(drone_view);

    if (server) {
        attach_drone_to_server(drone, server);
    }

    return drone;
}

void ServerController::attach_drone_to_server(Drone *drone, Server *server)
{
    if (drone->get_server_name() == server->get_name()) {
        return;
    }
    drone->set_server_name(server->get_name());
    server_drone_count_[server]++;
    direction_controller_->set_drone_target(drone, server->get_position());
}

void ServerController::detach_drone_from_server(Drone *drone)
{
    if (drone->get_server_name().empty()) {
        return;
    }
    auto* server = find_server_by_name(drone->get_server_name());
    server_drone_count_[server]--;
    drone->set_server_name("");
}

void ServerController::delete_server(Server *server)
{
    window_->removeView(server_view_[server]);
    auto iter = server_view_.find(server);
    if (iter != server_view_.end()) {
        server_view_.erase(iter);
    }
    VectorUtil::delete_object(servers_, server);
}

void ServerController::delete_drone(Drone *drone)
{
    window_->removeView(drone_view_[drone]);
    auto iter = drone_view_.find(drone);
    if (iter != drone_view_.end()) {
        drone_view_.erase(iter);
    }
    detach_drone_from_server(drone);
    VectorUtil::delete_object(drones_, drone);
}

int ServerController::get_server_attached_drone_count(Server *server)
{
    return server_drone_count_[server];
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
                std::string area_color = values[2];

                Server *server = new Server(name, area_color);

                string x_string = StringUtil::trim(position[0]);
                server->get_position().x_ = VectorUtil::string_cast_to<float>(x_string);
                server->get_position().y_ = VectorUtil::string_cast_to<float>(position[1]);

                add_server(server);
            }
        }
    }, [this, &on_loaded] () {
        ServerReadyEvent server_ready_event(servers_);
        event_manager_->publish(EventType::SERVER_READY, &server_ready_event);
        on_loaded();
    });
}

void ServerController::save_current_state(const TypeUtil::Callback& on_finish)
{
    std::string config_file = ServerController::get_config_file();
    FileStream out_stream(config_file, {";", true});

    auto writer = out_stream.writer();

    int i(0);
    for (Server* server: servers_) {
        std::string pos = "(" + std::to_string(server->get_position().x_) + "," + std::to_string(server->get_position().y_) + ")";
        writer.write(i, 0, server->get_name());
        writer.write(i, 1, pos);
        writer.write(i, 2, server->get_color());
        i++;
    }

    writer.persist(on_finish);
}

std::vector<Server *>& ServerController::servers()
{
    return servers_;
}

std::vector<Drone*>& ServerController::drones()
{
    return drones_;
}

InputManager::KeyPressListener ServerController::on_key_pressed()
{
    return [this] (InputManager::Key key, InputManager::MousePosition position) {
        switch (key) {
            case InputManager::ENTER:
                create_drone(where_send_drone());
                break;
            case InputManager::F1:
                set_servers_color(get_selected_servers(), "RED");
                break;
            case InputManager::F2:
                set_servers_color(get_selected_servers(), "BLACK");
                break;
            case InputManager::F3:
                set_servers_color(get_selected_servers(), "CYAN");
                break;
            case InputManager::F4:
                set_servers_color(get_selected_servers(), "YELLOW");
                break;
            case InputManager::F5:
                set_servers_color(get_selected_servers(), "GREY");
                break;
            case InputManager::F6:
                set_servers_color(get_selected_servers(), "BLUE");
                break;
            case InputManager::F7:
                set_servers_color(get_selected_servers(), "ORANGE");
                break;
            case InputManager::F8:
                set_servers_color(get_selected_servers(), "PINK");
                break;
            case InputManager::F9:
                set_servers_color(get_selected_servers(), "GREEN");
                break;
            case InputManager::S:
                save_current_state();
                break;
            case InputManager::D:
                break;
            case InputManager::DEL:
                delete_selected_servers();
                break;
        }
    };
}

InputManager::MouseMoveListener ServerController::on_mouse_move()
{
    return [this] (InputManager::MousePosition position) {
    };
}

InputManager::MouseClickListener ServerController::on_mouse_click()
{
    return [this] (InputManager::MouseClick click, InputManager::MousePosition position) {
    };
}

EventManager::Subscription ServerController::on_background_ready()
{
    return [this] (Event* e, const TypeUtil::Callback& unsubscribe) {
        BackgroundReadyEvent* background_ready_event = (BackgroundReadyEvent*)e;
        VoronoiDiagramView* voronoi_diagram_view = new VoronoiDiagramView(background_ready_event->get_voronoi_diagram());
        window_->addView(voronoi_diagram_view, true);
        for (auto& server_view: server_view_) {
            window_->addView(server_view.second);
        }
    };
}

Server *ServerController::where_send_drone()
{
    int choix = rand() % servers_.size();
    return servers_[choix];
}
