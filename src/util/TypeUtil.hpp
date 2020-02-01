//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#ifndef DRONEPROJECT_TYPEUTIL_HPP
#define DRONEPROJECT_TYPEUTIL_HPP

#include <string>
#include <functional>

namespace TypeUtil
{
    /**
     * @brief a type to define a function which is used as an error callback.
     */
    typedef std::function<void(const std::string& error)> ErrorCallback;

    /**
     * a type to define a function which is used as a callback.
     */
    typedef std::function<void()> Callback;
};


#endif //DRONEPROJECT_TYPEUTIL_HPP
