//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//


#include <utility>
#include <vector>
#include "Command.hpp"
#include "internal/ConfigCommand.hpp"

Command::Command(
        const char*  name,
        const char* shortcut,
        const char* description,
        const char* usage,
        bool value_required,
        ValidateCallback validate_function
    ) :
        name_(name),
        shortcut_(shortcut),
        description_(description),
        usage_(usage),
        given_(false),
        value_required_(value_required),
        value_(nullptr),
        validate_function_(std::move(validate_function))
{}

const char* Command::get_shortcut() const
{
    return shortcut_;
}

const char* Command::get_name() const
{
    return name_;
}

const char* Command::get_description() const
{
    return description_;
}

const char* Command::get_usage() const
{
    return usage_;
}

void Command::set_value(char* value)
{
    value_ = value;
}

const char*  Command::get_value() const
{
    return value_;
}

bool Command::is_value_required() const
{
    return value_required_;
}

char* Command::validate(char* value, std::vector<Command*> &options, TypeUtil::ErrorCallback& on_error)
{
    return validate_function_ != nullptr ? validate_function_(this, value, options, on_error) : value;
}

bool Command::is_given() const
{
    return given_;
}

void Command::set_given(bool given)
{
    given_ = given;
}

std::vector<Command *> Command::all_internals()
{
    std::vector<Command*> commands;
    commands.push_back(new ConfigCommand);
    return commands;
}
