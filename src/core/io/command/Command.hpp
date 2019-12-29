//
// Created by Maanrifa Bacar Ali on 19/12/2019.
//

#ifndef DRONEPROJECT_COMMAND_HPP
#define DRONEPROJECT_COMMAND_HPP

#include "../../../util/TypeUtil.hpp"

/**
 * This objects is the representation of an option and contain all its informations such as name, description, usage etc.
 *
 * @author Maanrifa Bacar Ali <dev.manrif@gmail.com>
 */
class Command {

public:

    typedef std::function<char*(Command*, const char*, std::vector<Command*>&, TypeUtil::ErrorCallback& error)> ValidateCallback;

    /**
     * Main constructor
     *
     * @param name The name of the option
     * @param shortcut The shortcut of the option
     * @param description The description of the option
     * @param usage The usage examples of the option
     * @param value_required If a value is expected for the option
     * @param validate_function A function that will be called for validating an user given argument for the option.
     *                          Only for dynamic options.
     */
    Command(
            const char* name,
            const char* shortcut,
            const char* description,
            const char* usage,
            bool value_required,
            ValidateCallback  validate_function = nullptr
    );

    const char* get_shortcut() const;

    const char* get_name() const;

    const char* get_description() const;

    const char* get_usage() const;

    bool is_given() const;

    void set_given(bool given);

    void set_value(char* value);

    virtual const char*  get_value() const;

    bool is_value_required() const;

    /**
     * This function will be called for validating an option argument
     *
     * @param value The user given argument
     * @param options The options list
     * @param on_error A callable that can be called if something wrong and that will finish the program.
     * @return A valid argument of a default one
     */
    virtual char* validate(char* value, std::vector<Command*>& options, TypeUtil::ErrorCallback& on_error);

    static std::vector<Command*> all_internals();

protected:

    char* value_;

private:

    const char* shortcut_;
    const char* name_;
    const char* description_;
    const char* usage_;

    bool value_required_;
    bool given_;

    const ValidateCallback validate_function_;

};

#endif //DRONEPROJECT_COMMAND_HPP
