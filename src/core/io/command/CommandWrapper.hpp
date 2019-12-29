//
// Created by Maanrifa Bacar Ali on 24/12/2019.
//

#ifndef DRONEPROJECT_COMMANDWRAPPER_HPP
#define DRONEPROJECT_COMMANDWRAPPER_HPP


#include <vector>
#include "Command.hpp"

/**
 * A wrapper class to facilitate access to information concerning the arguments.
 *
 * @author Maanrifa Bacar Ali <dev.manrif@gmail.com>
 */
class CommandWrapper
{

public:

    /**
     * Main constructor
     *
     * @param options The options list
     */
    explicit CommandWrapper(std::vector<Command*>& options);

    /**
     *
     * @param option The option for which value has to be updated
     * @return the value of the requested option if available
     * @throw std::logic_exception an exception if the option didn't exists
     */
    const char* get_value(const char* option) const;

    /**
     *
     * @param option The option for which value has to be updated
     * @param value The value
     * @throw std::logic_exception if the option didn't exists
     */
    void set_value(const char* option, char* value);

    /**
     *
     * @param option The option for which availability is needed
     * @return True if the requested option is available
     */
    bool has(const char* option);

private:

    Command* get_command(const char* option, bool strict = true) const;

    std::vector<Command*>& options_;
};


#endif //DRONEPROJECT_COMMANDWRAPPER_HPP
