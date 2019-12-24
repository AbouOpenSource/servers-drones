//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_CONFIGCOMMAND_HPP
#define DRONEPROJECT_CONFIGCOMMAND_HPP


#include <vector>
#include "../Command.hpp"

class ConfigCommand: public Command
{

public:

    ConfigCommand();

    char* validate(char *value, std::vector<Command *> &options, std::function<void(const std::string &)> &on_error) override;

    const char* get_value() const override;

private:

    static constexpr const char* DEFAULT_FILE = "./data/servers.txt";

};


#endif //DRONEPROJECT_CONFIGCOMMAND_HPP
