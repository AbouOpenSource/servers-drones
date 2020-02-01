#ifndef DRONEPROJECT_VECTORUTIL_HPP
#define DRONEPROJECT_VECTORUTIL_HPP

#include <vector>

namespace VectorUtil
{
    /**
    * @brief print a one dimensional vector.
    * @tparam T the generic type of the 1 dimensional vector.
    * @param vector the 1 dimensional vector to print.
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

    /**
     * @brief erase an object inside a vector.
     * @tparam T the generic type of the object.
     * @param vector the vector where we must remove the object.
     * @param object the object to remove.
     */
    template <typename T>
    void delete_object(std::vector<T*> &vector, T* object);

    /**
    * @brief erase an object inside a vector.
    * @tparam T the generic type of the object.
    * @param vector the vector where we must remove the object.
    * @param object the object to remove.
    */
    template <typename T>
    void delete_object(std::vector<T> &vector, T* object);

    /**
     * @brief execute the callback function "init_function" while the vector size of the vector
     * passed in parameter is smaller than the expected size.
     * @tparam T the type of the vector.
     * @param vector the vector on which we check the size.
     * @param expected_size the limit size.
     * @param init_function the callback function.
     */
    template <typename T>
    void ensure_size(const std::vector<T>& vector, unsigned long expected_size, const std::function<void()>& init_function);
};

#include "VectorUtil.tcc"

#endif //DRONEPROJECT_VECTORUTIL_HPP