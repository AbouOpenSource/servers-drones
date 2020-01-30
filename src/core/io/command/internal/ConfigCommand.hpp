//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_CONFIGCOMMAND_HPP
#define DRONEPROJECT_CONFIGCOMMAND_HPP

#include <vector>
#include "../Command.hpp"
#include "../../../../../data/config/config.hpp"

#define FILE_PATH_REGEX R"(^(?:[a-zA-Z]\:(\\|\/)|\\\\|\.(\/|\\)|\/)([^\\\/\:\*\?\<\>\"\|]+(\\|\/)?)+.txt$)"

class ConfigCommand: public Command
{

public:

    ConfigCommand();

    char *validate(char *value, std::vector<Command *> &options, TypeUtil::ErrorCallback &on_error) override;

    const char* get_value() const override;

};


#endif //DRONEPROJECT_CONFIGCOMMAND_HPP
