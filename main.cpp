/* For testing purposes */

#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"

int main() {
    span::Matrix<int> A({2, 2});
    A._data[0] = 3;
    A._data[1] = 2;
    A._data[3] = 9;

    std::vector<int> v{1, 2, 0, 9};
    std::vector<int> u{0};

    std::cout << span::dot_product<int>(u, v) << std::endl;

    return 0;
}
