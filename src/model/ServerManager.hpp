//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERMANAGER_HPP
#define DRONEPROJECT_SERVERMANAGER_HPP


#include <string>
#include <vector>
#include "../core/ServiceProvider.hpp"
#include "../core/event/input/InputManager.hpp"
#include "Server.hpp"
#include "../util/TypeUtil.hpp"
#include "../core/event/EventManager.hpp"
#include <thread>


class ServerManager: public ServiceProvider
{

public:

    static std::string SERVICE;


    ServerManager();

    Server* get_server_at(InputManager::MousePosition position);

    std::vector<Server*> get_selected_servers();

    void delete_selected_servers();

    void clear_selection();

    void save_state(TypeUtil::Callback on_finish = nullptr);

    void set_servers_color(std::vector<Server*> servers);

    void add_server(Server* server);

    void add_server_at(Server* server, InputManager::MousePosition position);

    std::thread for_start_thread();
    void to_call_each_time();

private:

    InputManager::KeyPressListener on_key_pressed();

    InputManager::MouseMoveListener on_mouse_move();

    InputManager::MouseClickListener on_mouse_click();

    EventManager* event_manager_;

    std::vector<Server *> servers_;

};


#endif //DRONEPROJECT_SERVERMANAGER_HPP
