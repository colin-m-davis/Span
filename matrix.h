#include "tensor.h"

namespace span {

template<typename T>
class Matrix : public Tensor<T, 2> {

public:
    Matrix(std::array<int, 2> shape, std::vector<T> data) : Tensor<T, 2>(shape, data) {}

};

}