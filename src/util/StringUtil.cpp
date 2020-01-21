//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#include <regex>
#include "StringUtil.hpp"
#include <sstream>

std::string StringUtil::trim(std::string &target)
{
    return std::regex_replace(target, std::regex("^ +| +$|( ) +"), "$1");
}

std::vector<std::string> StringUtil::split(const std::string& line, const char& delimiter)
{
    int len = line.length();
    std::string ch;
    std::vector<std::string> array;

    for (int j = 0, k = 0; j < len; j++) {
        if (line[j] == delimiter) {
            ch = line.substr(k, j - k);
            array.push_back(ch);
            k = j+1;
        }
        if (j == len - 1) {
            ch = line.substr(k, j - k+1);
            array.push_back(ch);
        }
    }

    return array;
}

template <typename cast_type>
cast_type string_cast_to(std::string& string_value)
{
    std::istringstream reader(string_value);
    cast_type val;
    reader >> val;

    return val;
}
