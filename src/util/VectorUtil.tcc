#include <sstream>

#include "iostream"
#include "VectorUtil.hpp"

namespace VectorUtil {
    template <typename T>
    void print_1D_vector(std::vector<T> &vector)
    {
        // Check if the vector is empty.
        if (vector.empty())
        {
            std::cout << "Vector is empty!" << std::endl;
            return;
        }

        // If the vector isn't empty, print it.
        std::cout << '[';

        // Initialize a counter and print all the element of the vector.
        int index{0};
        for (auto &element: vector)
        {
            if (index != vector.size() - 1)
                std::cout << element << ", ";
            else
                std::cout << element;
            ++index;
        }

        std::cout << "]" << std::endl;
    }

    template<typename T>
    void print_2D_vector(const std::vector<std::vector<T>> &vector)
    {
        // Check if the vector is empty.
        if (vector.empty())
        {
            std::cout << "Vector is empty!" << std::endl;
            return;
        }

        // If the vector isn't empty, print it.
        std::cout << "[\n";
        unsigned int cell_count{0};

        for (const auto &vector_row: vector)
        {
            std::cout << "\t[";

            for (const auto &vector_cell: vector_row)
            {
                ++cell_count;
                if (cell_count != vector_row.size())
                    std::cout << vector_cell << ", ";
                else
                    std::cout << vector_cell << ']' << std::endl;
            }
            cell_count = 0;
        }

        std::cout << ']' << std::endl;
    }

    template <typename cast_type>
    cast_type string_cast_to(std::string& string_value)
    {
        std::istringstream reader(string_value);
        cast_type val;
        reader >> val;

        return val;
    }

    template<typename T>
    void delete_object(std::vector<T*>& vector, T *object)
    {
        vector.erase(std::remove_if(vector.begin(), vector.end(), [&object](T* i) {
            return i && (i == object);
        }));
    }

    template<typename T>
    void delete_object(std::vector<T>& vector, T *object)
    {
        vector.erase(std::remove_if(vector.begin(), vector.end(), [&object](T i) {
            return &i == object;
        }));
    }

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