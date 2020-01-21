#include <vector>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/gui/Window.hpp"
#include "src/core/ServiceContainer.hpp"
#include "src/gui/drawable/Circumscribe.hpp"

using namespace std;

int main(int argc, char** argv)
{

    // Command Service
    std::vector<Command*> commands(Command::all_internals());
    CommandParser command_parser(commands, true);
    CommandContainer command_container = command_parser.parse(argc, argv);

    // Input Service
    InputManager input_manager;

    // Window Service
    Window window(argc, argv, &input_manager);

    // Instantiating service container
    ServiceContainer* service_container = ServiceContainer::get_instance();
    service_container->register_service(&command_container);
    service_container->register_service(&input_manager);
    service_container->register_service(&window);

    /*Read servers data
    FileStream in_stream(command_wrapper.get_value("c"), {";", true});

    auto reader_interface = in_stream.reader();

    Usage example
    reader_interface.read([&write_interface] (const unsigned int row, const unsigned int col, const std::string& value) {
    }, [] () {
    });
    */

    Circumscribe circumscribe;

    window.addDrawable(&circumscribe);
    window.start();

    return 0;
}