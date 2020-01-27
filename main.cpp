#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/model/Polygon.hpp"
#include "src/controller/ServerController.hpp"
#include "src/Window.hpp"
#include "src/core/service/ServiceContainer.hpp"
#include "src/view/PolygonView.hpp"
#include "src/controller/CollisionController.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // Command Service
    std::vector<Command*> commands(Command::all_internals());
    CommandParser command_parser(commands, true);
    CommandContainer command_container = command_parser.parse(argc, argv);

    // Instantiating service container
    ServiceContainer* service_container = ServiceContainer::get_instance();
    service_container->register_service(&command_container);

    // Input Service
    InputManager input_manager;
    service_container->register_service(&input_manager);

    // Event Service;
    EventManager event_manager;
    service_container->register_service(&event_manager);

    // Window Service
    Window window(argc, argv);
    service_container->register_service(&window);

    // Direction Controller Service
    DirectionController direction_controller_;
    service_container->register_service(&direction_controller_);

    // Server Controller Service
    ServerController server_controller;
    service_container->register_service(&server_controller);

    // Collision Controller Service
    CollisionController collision_controller_;
    service_container->register_service(&collision_controller_);

    Polygon convex_polygon = Polygon();
    PolygonView polygon_view(&convex_polygon);

    // Init from last state
    server_controller.load_last_state([&window, &convex_polygon, &polygon_view, &server_controller] () {
        convex_polygon.init(server_controller.servers());
        window.addView(&polygon_view);

        Drone* drone_paris = server_controller.create_drone();
        Server* paris = server_controller.find_server_by_name("Paris");
        server_controller.attach_drone_to_server(drone_paris, paris);

        Drone* drone_beijing = server_controller.create_drone();
        Server* beijing = server_controller.find_server_by_name("Beijing");
        server_controller.attach_drone_to_server(drone_beijing, beijing);

        Drone* drone_san_francisco = server_controller.create_drone();
        Server* san_francisco = server_controller.find_server_by_name("San Francisco");
        server_controller.attach_drone_to_server(drone_san_francisco, san_francisco);

        Drone* drone_rome = server_controller.create_drone();
        Server* rome = server_controller.find_server_by_name("Rome");
        server_controller.attach_drone_to_server(drone_rome, rome);

        Drone* drone_rome1 = server_controller.create_drone();
        server_controller.attach_drone_to_server(drone_rome1, rome);


        Drone* drone_london = server_controller.create_drone();
        Server* london = server_controller.find_server_by_name("London");
        server_controller.attach_drone_to_server(drone_london, london);

        Drone* drone_berlin = server_controller.create_drone();
        Server* berlin = server_controller.find_server_by_name("Berlin");
        server_controller.attach_drone_to_server(drone_berlin, berlin);
    });

    window.start();

    return 0;
}