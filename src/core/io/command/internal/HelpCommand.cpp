//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include "HelpCommand.hpp"

HelpCommand::HelpCommand()
        : Command("help", "h", "Display this help text.", "-h", false)
{}

char* HelpCommand::validate(char *value, std::vector<Command *> &options, std::function<void(const std::string &)> &on_error)
{
    std::cout << "Drone project command table:\n\n" << std::left
              << std::setw(COLUMN_WIDTH_NAME) << "Command"
              << std::setw(COLUMN_WIDTH_SHORTCUT) << "Shortcut"
              << std::setw(COLUMN_WIDTH_DESCRIPTION) << "Description"
              << std::setw(COLUMN_WIDTH_USAGE)<< "Usage" << std::endl << std::endl;

    int max = options.size();
    for (int i = 0; i < max; ++i) {
        printOption(options[i]);
    }

    exit(0);
}

void HelpCommand::printOption(Command* option) const
{
    std::cout << std::left
              << std::setw(COLUMN_WIDTH_NAME) << option->get_name()
              << std::setw(COLUMN_WIDTH_SHORTCUT) << "-" << option->get_shortcut() << " (--" << option->get_name() << ")"
              << std::setw(COLUMN_WIDTH_DESCRIPTION) << option->get_description()
              << std::setw(COLUMN_WIDTH_USAGE) << option->get_usage() << std::endl;
}
