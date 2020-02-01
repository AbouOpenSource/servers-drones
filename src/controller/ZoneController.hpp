//
// Created by Maanrifa Bacar Ali on 29/01/2020.
//

#ifndef DRONEPROJECT_ZONECONTROLLER_HPP
#define DRONEPROJECT_ZONECONTROLLER_HPP


#include "Controller.hpp"
#include "../model/Drone.hpp"
#include "../model/Server.hpp"
#include "DiagramController.hpp"

class ZoneController: public Controller
{

public:

    struct ServerData {
        float expected;
        std::vector<Server*> neighbors;
        std::vector<Drone*> drones;
    };

    static std::string SERVICE;

    ZoneController();

    ServerData* get_server_data(Server* server);

private:

    void find_neighbors();

    void calculate_drones_distribution();

    void track_drone_zone_change();

    void send_target_event(Drone* drone, Server* server);

    void find_unfilled_neighbor(Drone* drone, Server* server);

    void add_drone_to_server(Drone* drone, Server* server);

    void remove_drone_from_server(Drone* drone, Server* avoid_server);

    bool is_server_full(Server* server);

    std::vector<Drone*> drones_;

    DiagramController* diagram_controller_;

    std::map<Server*, ServerData*> server_data_;
};


#endif //DRONEPROJECT_ZONECONTROLLER_HPP
