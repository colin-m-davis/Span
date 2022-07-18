/* For testing purposes */

#include "matrix.h"
#include <iostream>

int main() {
    span::Matrix<int> M = span::Matrix<int>({2, 3}, {1, 2, 3, 4});
    M._get_element({0, 1});
}

