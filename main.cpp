#include "src/core/service/ServiceContainer.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/core/event/EventManager.hpp"
#include "src/controller/DirectionController.hpp"
#include "src/controller/ServerController.hpp"
#include "src/controller/CollisionController.hpp"
#include "src/controller/DiagramController.hpp"
#include "src/Window.hpp"
#include "src/controller/ZoneController.hpp"

using namespace std;

int main(int argc, char** argv)
{
    // Instantiating service container
    ServiceContainer* service_container = ServiceContainer::get_instance();

    // Command Service
    std::vector<Command*> commands(Command::all_internals());
    CommandParser command_parser(commands, true);
    CommandContainer command_container = command_parser.parse(argc, argv);
    service_container->register_service(&command_container);

    // Event Service;
    EventManager event_manager;
    service_container->register_service(&event_manager);

    // Window Service
    Window window(argc, argv);
    service_container->register_service(&window);

    // Server Controller Service
    ServerController server_controller;
    service_container->register_service(&server_controller);

    // Diagram Controller Service
    DiagramController diagram_controller;
    service_container->register_service(&diagram_controller);

    // Direction Controller Service
    DirectionController direction_controller;
    service_container->register_service(&direction_controller);

    // Collision Controller Service
    CollisionController collision_controller;
    service_container->register_service(&collision_controller);

    // Zone Controller Service
    ZoneController zone_controller;
    service_container->register_service(&zone_controller);

    // Load last saved state
    server_controller.load_last_state();

    window.start();

    return 0;
}