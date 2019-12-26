#include <vector>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/core/io/reader/FileStream.hpp"

using namespace std;

int main(int argc, char** argv)
{

    // Init arguments
    std::vector<Command*> commands(Command::all_internals());
    CommandParser command_parser(commands, true);
    CommandWrapper command_wrapper = command_parser.parse(argc, argv);

    // Read servers data
    FileStream in_stream(command_wrapper.get_value("c"), {";", true});

    auto reader_interface = in_stream.reader();
    auto write_interface = in_stream.writer();

    // Usage example
    reader_interface.read([&write_interface] (const unsigned int row, const unsigned int col, const std::string& value) {
        // Write the same data
        write_interface.write(row, col, value);
    }, [&write_interface] () {
        // Store on disk
        write_interface.persist();
    });

    return 0;
}