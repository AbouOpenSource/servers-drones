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
        int current;
        std::vector<Server*> neighbors;
    };

    static std::string SERVICE;

    ZoneController();

    ServerData* get_server_data(Server* server);

private:

    void find_neighbors();

    void calculate_drones_distribution();

    void check_drones_distribution();

    void monitor_drone(Drone* drone);

    void track_drone_zone_change();

    bool compare(Server* server, Server* neighbor);

    Server* get_drone_current_zone_server(Drone* drone);

    std::vector<Drone*> drones_;

    DiagramController* diagram_controller_;

    std::map<Server*, ServerData*> server_data_;
};


#endif //DRONEPROJECT_ZONECONTROLLER_HPP
