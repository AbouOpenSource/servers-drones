//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#include "ConfigCommand.hpp"
#include <experimental/filesystem>

ConfigCommand::ConfigCommand()
        : Command("config", "c", "Set the config file absolute path.", "-c \"/home/foo/bar.txt\"", true)
{}

char *ConfigCommand::validate(char* value, std::vector<Command *> &options,
                              std::function<void(const std::string &)> &on_error)
{
    if (!std::experimental::filesystem::is_regular_file(value)) {
        on_error("The file \"" + std::string(value) + "\" is not a valid file.\nPlease give a valid file full path.");
    }
    return value;
}

const char* ConfigCommand::get_value() const
{
    return value_ ? value_ : DEFAULT_FILE;
}
