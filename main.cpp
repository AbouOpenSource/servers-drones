#include <vector>
#include <iostream>
#include "src/core/io/command/internal/ConfigCommand.hpp"
#include "src/core/io/command/CommandParser.hpp"

int main(int argc, char** argv)
{
    std::vector<Command*> commands(Command::all_internals());
    CommandParser command_parser(commands, true);
    CommandWrapper command_wrapper = command_parser.parse(argc, argv);

    std::cout << command_wrapper.get_value("c") << std::endl;

    return 0;
}