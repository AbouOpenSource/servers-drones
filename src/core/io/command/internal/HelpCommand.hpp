//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_HELPCOMMAND_HPP
#define DRONEPROJECT_HELPCOMMAND_HPP


#include "../Command.hpp"

#define COLUMN_WIDTH_NAME 20
#define COLUMN_WIDTH_SHORTCUT 20
#define COLUMN_WIDTH_DESCRIPTION 70
#define COLUMN_WIDTH_USAGE 30

class HelpCommand: public Command
{

public:

    HelpCommand();

    char* validate(char *value, std::vector<Command *> &options, TypeUtil::ErrorCallback& on_error) override;

    void printOption(Command* option) const ;

};


#endif //DRONEPROJECT_HELPCOMMAND_HPP
