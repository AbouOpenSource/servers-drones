//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_CONFIGCOMMAND_HPP
#define DRONEPROJECT_CONFIGCOMMAND_HPP

#include <vector>
#include "../Command.hpp"

#define DEFAULT_FILE_1 "./data/servers.txt"
#define DEFAULT_FILE_2 "../data/servers.txt"

class ConfigCommand: public Command
{

public:

    ConfigCommand();

    char *validate(char *value, std::vector<Command *> &options, TypeUtil::ErrorCallback &on_error) override;

    const char* get_value() const override;

};


#endif //DRONEPROJECT_CONFIGCOMMAND_HPP
