#include <iostream>
#include "src/model/Matrix.hpp"
#include "src/model/Window.hpp"

int main(int argc,char **argv) {
    Matrix<int> matrix(10);
//    std::cout << matrix.determinant();

//    std::cout << matrix;

    Window window("Triangulation", argc, argv);
    window.start();

    return 0;
}
