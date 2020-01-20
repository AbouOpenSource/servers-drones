#include <vector>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"
#include "src/core/io/reader/FileStream.hpp"
#include "src/model/Matrix.hpp"
#include "src/gui/Window.hpp"

using namespace std;

int main(int argc, char** argv)
{

    // Init arguments
    std::vector<Command*> commands(Command::all_internals());
    Command mickael("mickael","m","will print mickael","-m", true);
    commands.push_back(&mickael);
    CommandParser command_parser(commands, true);
    CommandWrapper command_wrapper = command_parser.parse(argc, argv);

    // Read servers data
    FileStream in_stream(command_wrapper.get_value("c"), {";", true});
    FileStream out_stream("../data/out.txt", {"///", true});

    auto reader_interface = in_stream.reader();
    auto write_interface = out_stream.writer();

    // Usage example
    reader_interface.read([&write_interface] (const unsigned int row, const unsigned int col, const std::string& value) {
        // Write the same data
        write_interface.write(row, col, value);
    }, [&write_interface] () {
        // Store on disk
        write_interface.persist();
    });

    Matrix<int> matrix(10);
    //std::cout << matrix.determinant();

    //std::cout << matrix;

    Window window("Triangulation", argc, argv);
    window.start();

    return 0;
}