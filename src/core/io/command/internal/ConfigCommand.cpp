//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#include <regex>
#include "ConfigCommand.hpp"

ConfigCommand::ConfigCommand()
        : Command("config", "c", "Set the config file absolute path.", "-c \"/home/foo/bar.txt\"", true)
{}

char *ConfigCommand::validate(char *value, std::vector<Command *> &options, TypeUtil::ErrorCallback& on_error)
{
    if (!std::regex_match(value, std::regex(FILE_PATH_REGEX))) {
        on_error("The file \"" + std::string(value) + "\" is not a valid file.\nPlease give a valid file full path.");
    }
    return value;
}

const char* ConfigCommand::get_value() const
{
    if (value_) {
        return value_;
    }
    return DEFAULT_CONFIG_FILE;
}
