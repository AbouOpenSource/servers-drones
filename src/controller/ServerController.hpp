//
// Created by Maanrifa Bacar Ali on 22/01/2020.
//

#ifndef DRONEPROJECT_SERVERCONTROLLER_HPP
#define DRONEPROJECT_SERVERCONTROLLER_HPP


#include <string>
#include <vector>
#include "../model/Server.hpp"
#include "../model/Drone.hpp"
#include "../model/Position.hpp"
#include "../core/service/ServiceProvider.hpp"
#include "../core/event/input/InputManager.hpp"
#include "../util/TypeUtil.hpp"
#include "../core/event/EventManager.hpp"
#include "../view/DroneView.hpp"
#include "../view/ServerView.hpp"
#include "../Window.hpp"
#include "DirectionController.hpp"

class ServerController: public ServiceProvider
{

public:

    static std::string SERVICE;

    ServerController();

    Server* find_server_by_name(const std::string& server_name);

    Drone* find_drone_by_id(int drone_id);

    Server* get_server_at(Position position);

    std::vector<Server*> get_selected_servers();

    void delete_selected_servers();

    void clear_selection();

    void set_servers_color(const std::vector<Server*>& servers, const std::string& color);

    void add_server(Server* server);

    void attach_drone_to_server(Drone* drone, Server* server);

    void detach_drone_from_server(Drone* drone);

    void load_last_state(const TypeUtil::Callback& on_loaded = nullptr);

    void save_current_state(const TypeUtil::Callback& on_saved = nullptr);

    Drone* create_drone(Server* server = nullptr);

    void delete_server(Server* server);

    void delete_drone(Drone* drone);

    int get_server_attached_drone_count(Server* server);

    vector<Server *> & servers();

    vector<Drone *> & drones();

private:

    static std::string get_config_file();

    InputManager::KeyPressListener on_key_pressed();

    InputManager::MouseMoveListener on_mouse_move();

    InputManager::MouseClickListener on_mouse_click();

    int drone_id_incrementer_;

    Window* window_;

    EventManager* event_manager_;

    DirectionController* direction_controller_;

    std::vector<Server *> servers_;

    std::vector<Drone*> drones_;

    std::map<Server*, ServerView*> server_view_;

    std::map<Drone*, DroneView*> drone_view_;

    std::map<Server*, int> server_drone_count_;


    Server *where_send_drone();
};


#endif //DRONEPROJECT_SERVERCONTROLLER_HPP
