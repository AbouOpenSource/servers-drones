#include "iostream"
#include <sstream>

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
        uint cell_count{0};

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

    template <typename cast_type>
    std::vector<std::vector<cast_type>> cast_2d_string_vector_to_vector_of(std::vector<std::vector<std::string>> &vector)
    {
        std::vector<std::vector<cast_type>> vector_of_cast_type{};
        // Check if the vector is empty.
        if (vector.empty())
        {
            std::cout << "Vector is empty!" << std::endl;
        }

        else
        {
            for (uint i = 0; i < vector.size(); i++)
            {
                vector_of_cast_type.push_back({});
                for (uint j = 0; j < vector.size(); j++)
                {
                    try
                    {
                        const double cell = string_cast_to<cast_type>(vector[i][j]);
                        vector_of_cast_type[i].push_back(cell);
                    }
                    catch(const std::invalid_argument &ia)
                    {
                        std::cerr << "Invalid argument: " << ia.what() << '\n';
                    }
                }
            }
        }

        return vector_of_cast_type;
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