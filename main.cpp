#include <vector>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/core/io/reader/FileStream.hpp"
#include "src/util/StringUtil.hpp"
#include "src/util/VectorUtil.hpp"

#include "src/model/Server.hpp"
#include "src/model/Polygon.hpp"

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

    // Retrieve service example

    /*
    ServiceContainer* container = ServiceContainer::get_instance();
    InputManager* input_manager = static_cast<InputManager *>(container->get_service(InputManager::SERVICE));
    input_manager->register_mouse_move_listener([this] (InputManager::MousePosition position) {})
     */

    //Read config file data
    FileStream in_stream(command_container.get_value("c"), {";", true});
    auto reader_interface = in_stream.reader();

    std::vector<Server> servers;

    Vector2D katmandou_pos = Vector2D(420, 430);
//    Vector2D katmandou_pos1 = Vector2D(500, 425);
    Vector2D katmandou_pos1 = Vector2D(280, 500);

    std::string katmandou_color = "RED";
    std::string katmandou_name = "Katmandou";

    Server katmandou(katmandou_name, katmandou_pos, katmandou_color);
    Server katmandou1(katmandou_name, katmandou_pos1, katmandou_color);

//    servers.push_back(katmandou);
//    servers.push_back(katmandou1);

    std::array<std::string, 3> values;
    
    reader_interface.read([&values, &servers] (const unsigned int row, const unsigned int col, const std::string& value) {
        values[col] = value;

        if (col == 2) {
            if (values[1].front() == '(' && values[1].back() == ')') {
                values[1].erase(values[1].begin());
                values[1].erase(values[1].end() - 1);

                std::vector<std::string> position = StringUtil::split(values[1], ',');

                string x_string = StringUtil::trim(position[0]);

                // TODO change the namespace of the string_cast_to method. Put it in StringUtil instead of VectorUtil.
                float x = VectorUtil::string_cast_to<float>(x_string);
                float y = VectorUtil::string_cast_to<float>(position[1]);

                std::string name = values[0];
                Vector2D server_pos(x, y);
                std::string area_color = values[2];
                //Color area_color = color_value_of(values[2]);

                Server server(name, server_pos, area_color);

//                std::cout << "name: " << server.get_name()
//                          << " position: x: " << server.getCurrentPosition().x_ << ", y: " << server.getCurrentPosition().y_
//                          << " color: " << server.get_color()
//                          << std::endl;

                servers.push_back(server);
            }
        }
    });

    Polygon convex_polygon = Polygon(servers);
    Circumscribe circumscribe(servers);

    window.addDrawable(&circumscribe);
    window.addDrawable(&convex_polygon);
    window.start();

    return 0;
}