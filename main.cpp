#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/model/Polygon.hpp"
#include "src/controller/ServerController.hpp"
#include "src/Window.hpp"
#include "src/core/service/ServiceContainer.hpp"
#include "src/view/PolygonView.hpp"

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

    // Server Manager Service
    ServerController server_manager;
    service_container->register_service(&server_manager);

    Polygon convex_polygon = Polygon();
    PolygonView polygon_view(&convex_polygon);

    // Init from last state
    server_manager.load_last_state([&window, &convex_polygon, &polygon_view, &server_manager] () {
        convex_polygon.init(server_manager.servers());
        window.addView(&polygon_view);
    });

    window.start();

    return 0;
}