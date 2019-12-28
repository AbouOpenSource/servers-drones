#ifndef DRONEPROJECT_MATRIX_HPP
#define DRONEPROJECT_MATRIX_HPP

#include <vector>

/**
 * @brief the template matrix class, it allow you to create and manipulate
 * matrix of numeric types (int, float, double...).
 * @tparam T the template type of the matrix.
 */
template <typename T>
class Matrix
{

    // Prevent the use of no numeric types.
    static_assert(std::is_arithmetic<T>::value, "Type must be numeric.");

public:
    /********** Constructor & destructor **********/

    /**
     * @brief default constructor, it initialize an empty matrix.
     */
    Matrix();

    /**
     * @brief a constructor to initialize a matrix with the same number of rows as columns.
     * @param number_of_rows_and_cols the number of rows and cols of the matrix.
     */
    Matrix(unsigned int number_of_rows_and_cols);

    /**
     * @brief a constructor to initialize a matrix with the possibility to have a different number of rows
     * and columns.
     * @param number_of_rows the number of rows of the matrix.
     * @param number_of_cols the number of cols of the matrix.
     */
    Matrix(unsigned int number_of_rows, unsigned int number_of_cols);

    /**
     * @brief a constructor to initialize a matrix with a default value for each cell of the matrix..
     * @param number_of_rows the number of rows of the matrix.
     * @param number_of_cols the number of cols of the matrix.
     * @param value the default value.
     */
    Matrix(unsigned int number_of_rows, unsigned int number_of_cols, T value);

    /**
     * @brief a constructor to initialize a matrix with a default value assign by the lambda function
     * passed in parameter.
     * @param number_of_rows_and_cols the number of rows and cols of the matrix.
     * @param val_func the lambda function which is applied, it gets the row and col for each
     * cell of the matrix.
     */
    Matrix(unsigned int number_of_rows_and_cols, std::function<T(unsigned int, unsigned int)> val_func);
    Matrix(unsigned int number_of_rows, unsigned int number_of_cols, std::function<T(unsigned int, unsigned int)> val_func);

    /**
     * @brief a constructor to initialize a matrix from a vector of vector of template.
     * @param vector the vector of vector of template.
     */
    Matrix(std::vector<std::vector<T>> &vector);

    /**
     * @brief a constructor to initialize a matrix from a vector of vector of string.
     * @param vector the vector of vector of string.
     */
    Matrix(std::vector<std::vector<std::string>> &vector);

    /**
     * @brief a copy constructor to initialize a matrix thanks to data of another matrix.
     * @param to_copy the matrix to copy.
     */
    Matrix(const Matrix &to_copy);

    /********** Miscellaneous methods **********/

    /**
     * @brief return the transpose of the matrix.
     * @return return the transpose of the matrix.
     */
    Matrix transpose();

    /**
     * @brief return the transpose of the matrix.
     * @return return the transpose of the matrix.
     */
    Matrix<T> transpose() const;

    /**
     * @brief Add a row in the matrix.
     * @param val the vector to insert as a new row.
     */
    void add_row(const std::vector<T>& val);

    /**
     * @briefA function to iterate over all elements of the matrix.
     * @param func_for_each_element A callback function which allow you to get each element of the matrix, one by one.
     */
    void foreach(std::function<void(T element)> func_for_each_element);

    /**
     * @brief A function to iterate over all elements of the matrix.
     * @param func_for_each_element A callback function which allow you to get the row index, the col index and the element
     * for each element of the matrix.
     */
    void foreach(std::function<void(unsigned int row_index, unsigned int col_index, T element)> func_for_each_element);

    /********** Operator overload **********/

    /**
     * @brief overload of the "[]" operator, it allows you to access at the vector
     * contains in the matrix.
     * @param row_number the row of the vector you want to access.
     * @return the vector at the corresponding row.
     */
    std::vector<T>& operator[](unsigned int row_number);

    /**
     * @brief Same as the other operator "[]" overload but with constant matrix.
     * @param row_number the row of the vector you want to access.
     * @return the vector at the corresponding row.
     */
    const std::vector<T>& operator[](unsigned int row_number) const;

    /**
     * @brief overload of the "=" operator, it allows to copy a matrix within an other matrix.
     * @param to_copy the matrix to copy.
     * @return *this.
     */
    Matrix& operator=(const Matrix& to_copy);

    /**
     * @brief print the matrix.
     * @tparam U the type of the matrix.
     * @param out the output stream.
     * @param matrix the matrix to print.
     * @return the output stream.
     */
    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<U>& matrix);

    /********** Capacity **********/

    /**
     * @brief check if the matrix is empty and return the result.
     * @return true if the matrix is empty, false otherwise.
     */
    bool empty() const noexcept;

    /**
     * @brief return the number of rows of the matrix (similar to number_of_rows() method).
     * @return the number of rows of the matrix
     */
    unsigned int size() const noexcept;

    /**
     * @brief return the entire size of the matrix L * H.
     * @return the entire size of the matrix L * H.
     */
    unsigned int full_size() const noexcept;

    /********** Getter **********/

    /**
     * @brief return the number of rows of the matrix.
     * @return the number of rows of the matrix.
     */
    unsigned int number_of_rows() const noexcept;

    /**
     * @brief return the number of cols of the matrix.
     * @return the number of cols of the matrix.
     */
    unsigned int number_of_cols() const noexcept;

    /**
     * @brief return the 2 dimensional vector of the matrix.
     * @return the 2 dimensional vector of the matrix.
     */
    const std::vector<std::vector<T>>& vector() const noexcept;

    int determinant();

    // DETERMINANT: MATRIX SOLUTION
    /**
     * @brief Recursive function for finding determinant of matrix.
     * n is current dimension of mat[][].
     * @param mat
     * @param n
     * @return
     */
    int determinant(Matrix<T> mat, size_t n);

    /**
     * @brief Function to get cofactor of mat[p][q] in temp[][]. n is current dimension of mat[][]
     */
    void getCofactor(Matrix<T> mat, Matrix<T> temp, int p, int q, int n);

//    DETERMINANT: VECTOR SOLUTION
//    int determinant(std::vector<std::vector<T>>& mat, size_t n);
//    void getCofactor(std::vector<std::vector<T>>& mat, std::vector<std::vector<T>>& temp, int p, int q, int n);

//    DETERMINANT: TEACHER SOLUTION
//    float determinant();
//    void getMinus1Matrix(const Matrix<T> &mat44,int shadowLin, int shadowCol);
private:
    /**
     * @brief the number of rows of the matrix.
     */
    unsigned int number_of_rows_;

    /**
     * @brief the number of cols of the matrix.
     */
    unsigned int number_of_cols_;

    /**
     * @brief the vector of the matrix.
     */
    std::vector<std::vector<T>> vector_;
};

#include "Matrix.tcc"

#endif //DRONEPROJECT_MATRIX_HPP
