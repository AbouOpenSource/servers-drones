//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#include "ServerManager.hpp"
#include "../core/event/input/InputManager.hpp"
#include "../core/ServiceContainer.hpp"

std::string ServerManager::SERVICE = "ServerService";

ServerManager::ServerManager(): ServiceProvider(ServerManager::SERVICE), servers_({})
{
    ServiceContainer* container = ServiceContainer::get_instance();
    event_manager_ = static_cast<EventManager *>(container->get_service(EventManager::SERVICE));
    auto* input_manager = static_cast<InputManager *>(container->get_service(InputManager::SERVICE));
    input_manager->register_key_press_listener(on_key_pressed());
    input_manager->register_mouse_move_listener(on_mouse_move());
    input_manager->register_mouse_click_listener(on_mouse_click());}

Server * ServerManager::get_server_at(InputManager::MousePosition position)
{
    for (Server* server: servers_) {
        // TODO: add selection margin
        if (server->getCurrentPosition().x_ == position.X && server->getCurrentPosition().y_ == position.Y) {
            return server;
        }
    }
    return nullptr;
}

std::vector<Server *> ServerManager::get_selected_servers()
{
    std::vector<Server*> selection = {};
    for (Server* server: servers_) {
        /*if (server->is_selected()) {
            selection.push_back(server);
        }*/
    }
    return selection;
}

void ServerManager::delete_selected_servers()
{
    // TODO: implement
}

void ServerManager::clear_selection()
{
    for (Server* server: servers_) {
        /*if (server->is_selected()) {
            server->set_selected(false);
        }*/
    }
}

void ServerManager::save_state(TypeUtil::Callback on_finish)
{
    // TODO: implement
}

void ServerManager::set_servers_color(std::vector<Server *> servers)
{
    // TODO: implement
}

void ServerManager::add_server(Server *server)
{
    // TODO: implement
}

void ServerManager::add_server_at(Server *server, InputManager::MousePosition position)
{
    // TODO: implement
}

InputManager::KeyPressListener ServerManager::on_key_pressed()
{
    return [this] (InputManager::Key key, InputManager::MousePosition position) {

    };
}

InputManager::MouseMoveListener ServerManager::on_mouse_move()
{
    return [this] (InputManager::MousePosition position) {

    };
}

InputManager::MouseClickListener ServerManager::on_mouse_click()
{
    return [this] (InputManager::MouseClick click, InputManager::MousePosition position) {

    };
}


std::thread ServerManager::for_start_thread() {
    return std::thread([=] { to_call_each_time(); });
}



void ServerManager::to_call_each_time(){

    while (true){
        std::cout<<"to each second"<<std::endl;

    }
   /* for (Server* server: servers_) {
        server->detectCollision();
    }*/
}