/* For testing purposes */

#include <iostream>
#include "matrix.hpp"

int main() {
    span::Matrix<int> A({2, 2});
    A._data[0] = 3;
    A._data[1] = 2;
    A._data[3] = 9;

    return 0;
}

