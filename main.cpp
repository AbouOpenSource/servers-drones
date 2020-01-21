#include <vector>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/core/io/reader/FileStream.hpp"
#include "src/model/Matrix.hpp"
#include "src/util/StringUtil.hpp"
#include "src/util/VectorUtil.hpp"
#include "src/model/Server.hpp"
#include "src/gui/Window.hpp"

using namespace std;

int main(int argc, char** argv)
{

    // Init arguments
    std::vector<Command*> commands(Command::all_internals());

    CommandParser command_parser(commands, true);
    CommandWrapper command_wrapper = command_parser.parse(argc, argv);

    // Read servers data
    FileStream in_stream(command_wrapper.get_value("c"), {";", true});
    FileStream out_stream("../data/out.txt", {"///", true});

    auto reader_interface = in_stream.reader();
    auto write_interface = out_stream.writer();

    std::vector<Server> servers;
    std::array<std::string, 3> values;

    // Usage example
    reader_interface.read([&write_interface, &values, &servers] (const unsigned int row, const unsigned int col, const std::string& value) {
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
//                Color area_color = color_value_of(values[2]);

                Server server(name, server_pos, area_color);

                std::cout << "name: " << server.get_name()
                          << " position: x: " << server.getCurrentPosition().x_ << ", y: " << server.getCurrentPosition().y_
                          << " color: " << server.get_color()
                          << std::endl;

                servers.push_back(server);
            }
        }
    }, [&write_interface] () {
        // Store on disk
        write_interface.persist();
    });

//    Window window("Triangulation", argc, argv, servers);
//    window.start();

    return 0;
}