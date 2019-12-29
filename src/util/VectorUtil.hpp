#ifndef DRONEPROJECT_VECTORUTIL_HPP
#define DRONEPROJECT_VECTORUTIL_HPP

#include <vector>

namespace VectorUtil
{
    /**
    *  @brief: Print a one dimensional vector.
    *  @param: A vector that we want to be print.
    *  @return: void.
    */
    template <typename T>
    void print_1D_vector(std::vector<T> &vector);

    /**
     * @brief print a 2 dimensional vector.
     * @tparam T the generic type of the 2 dimensional vector.
     * @param vector the 2 dimensional vector to print.
     */
    template<typename T>
    void print_2D_vector(const std::vector<std::vector<T> > &vector);

    /********** TEMP **********/

    template <typename cast_type>
    cast_type string_cast_to(std::string& string_value);

    template <typename cast_type>
    std::vector<std::vector<cast_type>> cast_2d_string_vector_to_vector_of(std::vector<std::vector<std::string>> &vector);
};

#include "VectorUtil.tcc"

#endif //DRONEPROJECT_VECTORUTIL_HPP