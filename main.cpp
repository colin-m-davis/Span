/* For testing purposes */

#include "matrix.h"
#include <iostream>

int main() {
    span::Matrix<int> A = span::Matrix<int>({2, 3});
    A._data = {
        1, 2, 3,
        4, 5, 6
    };
    span::Matrix<int> B = span::Matrix<int>({3, 2});
    B._data = {
        5, 4,
        3, 8,
        7, 6
    };
    span::Matrix<int> C = span::mult(A, B);
    std::cout << C._get_element({1, 0}) << std::endl;
}

