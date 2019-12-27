#include "../../util/vector_util/VectorUtil.hpp"

/********** Constructor & Destructor **********/

template <typename T>
Matrix<T>::Matrix()
        : number_of_rows_{0},
          number_of_cols_{0},
          vector_{0}
{
}

template <typename T>
Matrix<T>::Matrix(unsigned int number_of_rows_and_cols)
        : number_of_rows_{number_of_rows_and_cols},
          number_of_cols_{number_of_rows_and_cols}
{
    vector_.resize(number_of_rows_and_cols);

    for (size_t i = 0; i < number_of_rows_and_cols; i++)
    {
        vector_[i].resize(number_of_rows_and_cols);
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int number_of_rows, unsigned int number_of_cols)
        : number_of_rows_{number_of_rows},
          number_of_cols_{number_of_cols}
{
    vector_.resize(number_of_rows);

    for (size_t i = 0; i < number_of_rows; i++)
    {
        vector_[i].resize(number_of_cols);
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int number_of_rows, unsigned int number_of_cols, T value)
        : number_of_rows_{number_of_rows},
          number_of_cols_{number_of_cols}
{
    vector_.resize(number_of_rows);

    for (size_t i = 0; i < number_of_rows; i++)
    {
        vector_[i].resize(number_of_cols, value);
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int number_of_rows, unsigned int number_of_cols, std::function<T(unsigned int, unsigned int)> val_func)
        : number_of_rows_{number_of_rows},
          number_of_cols_{number_of_cols}
{
    vector_.resize(number_of_rows);

    for (size_t i = 0; i < number_of_rows; i++)
    {
        vector_[i].resize(number_of_cols);
        for (size_t j = 0; j < number_of_cols; j++)
        {
            vector_[i][j] = val_func(i, j);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int number_of_rows_and_cols, std::function<T(unsigned int, unsigned int)> val_func)
        : number_of_rows_{number_of_rows_and_cols},
          number_of_cols_{number_of_rows_and_cols}
{
    vector_.resize(number_of_rows_and_cols);
    for (size_t i = 0; i < number_of_rows_and_cols; i++)
    {
        vector_[i].resize(number_of_rows_and_cols);
        for (size_t j = 0; j < number_of_rows_and_cols; j++)
        {
            vector_[i][j] = val_func(i, j);
        }
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>>& vector)
{
    if (vector.empty())
    {
        number_of_rows_ = 0;
        number_of_cols_ = 0;
        vector_ = vector;
    }
    else
    {
        unsigned int row_size = vector[0].size();

        for (const auto &vector_row: vector)
            if (vector_row.size() != row_size)
                throw std::invalid_argument("Size of rows inside the vector aren't constants.");

        number_of_rows_ = vector.size();
        number_of_cols_ = row_size;
        vector_ = vector;
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<std::string>>& vector)
{
    if (vector.empty())
    {
        number_of_rows_ = 0;
        number_of_cols_ = 0;
        vector_ = {};
    }
    else
    {
        unsigned int row_size = vector[0].size();

        for (const auto &vector_row: vector)
            if (vector_row.size() != row_size)
                throw std::invalid_argument("Size of rows inside the vector aren't constants.");

        number_of_rows_ = vector.size();
        number_of_cols_ = row_size;
        vector_ =  Utils::cast_2d_string_vector_to_vector_of<T>(vector);
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& to_copy)
{
    number_of_rows_ = to_copy.number_of_rows_;
    number_of_cols_ = to_copy.number_of_cols_;
    vector_ = to_copy.vector_;
}

/********** getters **********/

template <typename T>
unsigned int Matrix<T>::number_of_rows() const noexcept
{
    return number_of_rows_;
}

template <typename T>
unsigned int Matrix<T>::number_of_cols() const noexcept
{
    return number_of_cols_;
}

template <typename T>
const std::vector<std::vector<T>>& Matrix<T>::vector() const noexcept
{
    return vector_;
}

/*********** Operator overloading **********/

template <typename T>
std::vector<T>& Matrix<T>::operator[](const unsigned int row_number)
{
    return vector_[row_number];
}

template <typename T>
const std::vector<T>& Matrix<T>::operator[](unsigned int row_number) const
{
    return vector_[row_number];
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& to_copy)
{
    // On vérifie que l'objet n'est pas le même que celui passé en argument
    if (this != &to_copy)
    {
        // We copy all member's object.
        number_of_rows_ = to_copy.number_of_rows_;
        number_of_cols_ = to_copy.number_of_cols_;
        vector_ = to_copy.vector_;
    }

    // We return the object himself
    return *this;
}

template <typename U>
std::ostream& operator<<(std::ostream& out, const Matrix<U>& matrix)
{
    const unsigned int INF{std::numeric_limits<U>::max()};

    // Check if the vector is empty.
    if (matrix.empty()) {
        out << "Matrix is empty!" << std::endl;
        return out;
    }

    // If the vector isn't empty, print it.
    out << "[\n";
    unsigned int cell_count{0};

    for (const auto &vector_row: matrix.vector()) {
        out << "\t[";

        for (const auto &vector_cell: vector_row) {
            ++cell_count;
            if (cell_count != vector_row.size())
            {
                if (vector_cell == INF)
                    out << "∞" << ", ";
                else
                    out << vector_cell << ", ";
            }
            else
            {
                if (vector_cell == INF)
                    out << "∞" << "]" << std::endl;
                else
                    out << vector_cell << ']' << std::endl;
            }
        }
        cell_count = 0;
    }
    out << ']' << std::endl;

    return out;
}

/********** Capacity **********/

template <typename T>
unsigned int Matrix<T>::size() const noexcept
{
    return number_of_rows_;
}

template <typename T>
unsigned int Matrix<T>::full_size() const noexcept
{
    return number_of_rows_ * number_of_cols_;
}

template <typename T>
bool Matrix<T>::empty() const noexcept
{
    return vector_.empty();
}

/********** Modifiers **********/

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> new_matrix{number_of_rows_, number_of_cols_, [&](unsigned int row_index, unsigned int col_index) {
        return vector_[col_index][row_index];
    }};

    return new_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    Matrix<T> new_matrix{number_of_rows_, number_of_cols_, [&](unsigned int row_index, unsigned int col_index) {
        return vector_[col_index][row_index];
    }};

    return new_matrix;
}

template <typename T>
void Matrix<T>::add_row(const std::vector<T>& val)
{
    vector_.push_back(val);
}

/********** Miscellaneous **********/

template <typename T>
void Matrix<T>::foreach(std::function<void(uint row_index, uint col_index, T element)> func_for_each_element)
{
    for (uint i = 0; i < vector_.size(); i++)
    {
        for (uint j = 0; j < vector_[i].size(); j++)
        {
            func_for_each_element(i, j, vector_[i][j]);
        }
    }
}

// Function to get cofactor of mat[p][q] in temp[][]. n is current
// dimension of mat[][]
template <typename T>
void Matrix<T>::getCofactor(Matrix<T>& mat, Matrix<T>& temp, int p, int q, int n)
{
    int i = 0, j = 0;

    // Looping for each element of the matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of mat[][]. */
template <typename T>
int Matrix<T>::determinant()
{
    return determinant(*this, size());
}

template <typename T>
int Matrix<T>::determinant(Matrix<T>& mat, size_t n)
{
    int D = 0; // Initialize result.

    std::cout << "size: " << n << std::endl;

    //  Base case : if matrix contains single element.
    if (n == 1)
    {
        return mat[0][0];
    }

    Matrix<T> temp(mat.number_of_rows_, mat.number_of_rows_); // To store cofactors

    int sign = 1;  // To store sign multiplier.

    // Iterate for each element of first row.
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of mat[0][f].
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

//template <typename T>
//Matrix<T> Matrix<T>::address()
//{
//    return *this;
//}