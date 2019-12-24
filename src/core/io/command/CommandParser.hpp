//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_COMMANDPARSER_HPP
#define DRONEPROJECT_COMMANDPARSER_HPP


#include <vector>
#include "Command.hpp"
#include "CommandWrapper.hpp"

/**
 * A class that parse arguments and will setup options with their values and availability.
 *
 * @author Maanrifa Bacar Ali <dev.manrif@gmail.com>
 */
class CommandParser
{

public:

    /**
     *
     * @param options The list of options for which the parse will looks for availability and will complete.
     * @param strict If true, any additional option will finish the program with appropriated message.
     */
    CommandParser(std::vector<Command*> &options, bool strict);

    /**
     * Complete the options list.
     *
     * @param argc The arguments count
     * @param args The arguments list
     * @return
     * @see CommandWrapper
     */
    CommandWrapper parse(int argc, char** args);

private:

    std::vector<Command*> options_;

    bool strict_;

};


#endif //DRONEPROJECT_COMMANDPARSER_HPP
