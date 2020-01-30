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
#include "../util/TypeUtil.hpp"
#include "../core/event/EventManager.hpp"
#include "../view/DroneView.hpp"
#include "../view/ServerView.hpp"
#include "../Window.hpp"
#include "Controller.hpp"
#include "../../data/config/config.hpp"

class ServerController: public Controller
{

public:

    static std::string SERVICE;

    ServerController();

    Server* create_server(const std::string& name, const std::string& color, int x, int y);

    Server* find_server_by_name(const std::string& server_name);

    Server* get_server_at(Position position);

    Drone* create_drone();

    Drone* find_drone_by_id(int drone_id);

    Drone* get_drone_at(Position position);

    void delete_server(Server* server);

    void delete_drone(Drone* drone);

    void attach_drone_to_server(Drone* drone, Server* server);

    void detach_drone_from_server(Drone* drone);

    void load_last_state(const TypeUtil::Callback& on_loaded = nullptr);

    void save_current_state(const TypeUtil::Callback& on_saved = nullptr);

    int get_server_attached_drone_count(Server* server);

    vector<Server *> & servers();

    vector<Drone *> & drones();

private:

    static std::string get_config_file();

    std::vector<Server*> get_selection();

    void delete_selection();

    void clear_selection();

    void color_selection(const std::string& color);

    std::string get_next_color();

    void on_input(const char* input_type, Event* event);

    /*****************************************/

    int drone_id_incrementer_;

    Window* window_;

    std::vector<Server *> servers_;

    std::vector<Drone*> drones_;

    std::map<Server*, ServerView*> server_view_;

    std::map<Drone*, DroneView*> drone_view_;

    std::map<Server*, std::vector<Drone*>> server_drones_;
};


#endif //DRONEPROJECT_SERVERCONTROLLER_HPP
