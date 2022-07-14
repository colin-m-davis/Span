/* For testing purposes */

#include "linalg.h"
#include <iostream>

int main() {
    tensor<int> x = tensor<int>({3, 4, 5, 6}, {9, 9, 9, 9});
    std::vector<int> z = x._indices_from_index(200);
    matrix<int> a(2, 3, {3, 3, 3, 2, 1, 4});
    std::cout << a._get_element({1, 2});
}