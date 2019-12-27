#include <iostream>
#include "src/model/matrix/Matrix.hpp"
#include "src/model/window/Window.hpp"
#include "src/util/vector_util/VectorUtil.hpp"


int main(int argc,char **argv) {
    Matrix<int> matrix(10);
    std::cout << matrix.determinant();
//    matrix[1][2] = 3;
//    std::cout << matrix;

    Window window("Triangulation", argc, argv);
    window.start();

    return 0;
}
