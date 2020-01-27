#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/model/Polygon.hpp"
#include "src/controller/ServerController.hpp"
#include "src/Window.hpp"
#include "src/core/service/ServiceContainer.hpp"
#include "src/controller/CollisionController.hpp"
#include "src/model/VoronoiDiagram.hpp"
#include "src/view/VoronoiDiagramView.hpp"
#include "src/controller/DiagramController.hpp"

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

    // Diagram Controller Service
    DiagramController diagram_controller_;
    service_container->register_service(&diagram_controller_);

    // Init from last state
    server_controller.load_last_state([&window, &server_controller, &service_container] () {

//        for (Server* server: server_controller.servers())
//        {
//            Drone* drone = server_controller.create_drone();
//            Server* server_to_create = server_controller.find_server_by_name(server->get_name());
//            server_controller.attach_drone_to_server(drone, server_to_create);
//        }

    });

    window.start();

    return 0;
}