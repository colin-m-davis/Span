/* For testing purposes */

#include "linalg.cpp"
#include <iostream>

int main() {
    tensor<int> x = tensor<int>({3, 4, 5, 6});
    std::vector<int> z = x._indices_from_index(200);
    return 0;
}