//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#ifndef DRONEPROJECT_STRINGUTIL_HPP
#define DRONEPROJECT_STRINGUTIL_HPP

#include <string>
#include <sstream>

namespace StringUtil
{
    /**
     * @brief deletes the space at the beginning and of a string.
     * @param target the string where we want to deletes the space.
     * @return the new string without the spaces.
     */
    std::string trim(std::string& target);

    /**
     * @brief transform a string into a vector bounded by a delimiter character.
     * @param line the string to transform.
     * @param delimiter the delimiter to bound.
     * @return the vector.
     */
    std::vector<std::string> split(const std::string& line, const char& delimiter);

    /**
     * @brief cast a string into a new type, usually a float or an integer.
     * @tparam cast_type the type to cast the string in.
     * @param string_value the string to cast.
     * @return the value with its new type.
     */
    template <typename cast_type>
    cast_type string_cast_to(std::string& string_value)
    {
        std::istringstream reader(string_value);
        cast_type val;
        reader >> val;

        return val;
    }
};


#endif //DRONEPROJECT_STRINGUTIL_HPP
