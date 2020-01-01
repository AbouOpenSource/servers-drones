//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#ifndef DRONEPROJECT_TYPEUTIL_HPP
#define DRONEPROJECT_TYPEUTIL_HPP

#include <string>
#include <functional>

namespace TypeUtil
{

    typedef std::function<void(const std::string& error)> ErrorCallback;
    typedef std::function<void()> Callback;
};


#endif //DRONEPROJECT_TYPEUTIL_HPP
