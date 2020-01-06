//
// Created by Maanrifa Bacar Ali on 24/12/2019.
//

#include "CommandWrapper.hpp"
#include <vector>
#include <string>
#include <cstring>

CommandWrapper::CommandWrapper(std::vector<Command *>& options) : options_(options)
{}

const char* CommandWrapper::get_value(const char* option) const
{
    return get_command(option)->get_value();
}

void CommandWrapper::set_value(const char* option, char* value)
{
    get_command(option)->set_value(value);
}

bool CommandWrapper::has(const char* option)
{
    return get_command(option, true) != nullptr;
}

Command* CommandWrapper::get_command(const char* option, bool strict) const
{
    Command* command = nullptr;
    int i(0), max(options_.size());
    while (!command && i < max) {
        if (strcmp(options_[i]->get_name(), option) == 0 || strcmp(options_[i]->get_shortcut(), option) == 0) {
            command = options_[i];
        }
        i++;
    }

    if (strict && command == nullptr) {
        throw std::logic_error(std::string("Command ").append(option).append(" not found."));
    }

    return command;
}
