//
// Created by Maanrifa Bacar Ali on 25/12/2019.
//

#ifndef DRONEPROJECT_ARRAYUTIL_HPP
#define DRONEPROJECT_ARRAYUTIL_HPP

#include <vector>
#include <iostream>

namespace ArrayUtil
{
    template <typename T>
    void ensure_size(const std::vector<T>& vector, unsigned long expected_size, const std::function<void()>& init_function) {
        if (vector.size() > expected_size) {
            return;
        }
        int i(vector.size());
        while (i <= expected_size) {
            init_function();
            i++;
        }
    }
}


#endif //DRONEPROJECT_ARRAYUTIL_HPP
