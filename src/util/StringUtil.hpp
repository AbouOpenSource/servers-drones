//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#ifndef DRONEPROJECT_STRINGUTIL_HPP
#define DRONEPROJECT_STRINGUTIL_HPP


#include <string>

namespace StringUtil
{

    std::string trim(std::string& target);

    std::vector<std::string> split(const std::string& line, const char& delimiter);

    template <typename cast_type>
    cast_type string_cast_to(std::string& string_value);
};


#endif //DRONEPROJECT_STRINGUTIL_HPP
