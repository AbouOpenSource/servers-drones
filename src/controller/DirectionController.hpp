//
// Created by Maanrifa Bacar Ali on 24/01/2020.
//

#ifndef DRONEPROJECT_DIRECTIONCONTROLLER_HPP
#define DRONEPROJECT_DIRECTIONCONTROLLER_HPP


#include "../model/Drone.hpp"
#include "../core/service/ServiceContainer.hpp"
#include "../core/event/internal/EventType.hpp"

#define MAX_FORCE 200

class DirectionController: public ServiceProvider
{

public:

    static std::string SERVICE;

    struct MoveData {
        int delta_time = 1;
        int radius = 100;
        float weight = 10;
        float temps = 0;
        float w = 1;
        float theta_zero = 1000;
        float dx = 0;
        float dy = 0;
        float distance = 0;
        bool target_reached = false;
        bool circular_mode = false;
        Vector2D forces = {150000,150000};
        Vector2D acceleration = forces / weight;
        Vector2D speed = acceleration / (float) delta_time;
        Vector2D target = {0, 0};
    };

    struct DroneData {
        MoveData data;
        TypeUtil::Callback callback;
    };

    DirectionController();

    void set_drone_target(Drone* drone, const Vector2D& target);

    void prevent_collision_between_drones(Drone* d1, Drone* d2);

    float get_distance_between_drones(Drone* d1, Drone* d2) const;

    MoveData* get_instant_movement_for_drone(Drone* drone);

private:

    void ensure_map_contains(Drone* drone);

    void update_acceleration_of_drone(Drone* drone);

    void update_forces_of_drone(Drone* drone);

    void update_position_of_drone(Drone* drone);

    void update_speed_of_drone(Drone* drone);

    std::map<Drone*, DroneData> drone_data_;

};


#endif //DRONEPROJECT_DIRECTIONCONTROLLER_HPP
