//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#include <iostream>
#include "CommandParser.hpp"
#include "internal/HelpCommand.hpp"
#include "CommandContainer.hpp"

CommandParser::CommandParser(std::vector<Command*>& options, bool strict)
        : options_(options), strict_(strict)
{
    options_.insert(options_.begin(), new HelpCommand);
}

CommandContainer CommandParser::parse(int argc, char **args)
{
    std::string s_pre("-"), n_pre("--"), s_arg;
    int i(1), j(0), options_size(options_.size());
    bool value_expected(false);
    Command* option(nullptr);
    char* arg;

    TypeUtil::ErrorCallback on_error = [] (const std::string& error) {
        std::cout << error;
        exit(1);
    };

    while (i < argc) {
        arg = args[i];
        s_arg = arg;
        if (value_expected) {
            if (s_arg.rfind('-', 0) == 0) {
                on_error("Unexpected value \"" + s_arg + "\" for option -" + option->get_shortcut() + ".");
            }
            option->set_value(option->validate(arg, options_, on_error));
            option = nullptr;
            value_expected = false;
        } else {
            while (!option && j < options_size) {
                if ((n_pre + options_[j]->get_name()) == s_arg || (s_pre + options_[j]->get_shortcut()) == s_arg) {
                    option = options_[j];
                    option->set_given(true);
                    if (option->is_value_required()) {
                        value_expected = true;
                    }
                }
                j++;
            }

            if (!option && strict_) {
                on_error("Unsupported option ”" + s_arg  + "”.");
            } else if (option && !value_expected){
                option->validate(arg, options_, on_error);
                option = nullptr;
            }
            j = 0;
        }
        i++;
    }

    return CommandContainer(options_);
}
