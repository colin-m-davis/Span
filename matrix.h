#include "tensor.h"

// a series of operations available to Tensors of rank 2 (which I am equating to matrices for the purpose of this library)

namespace span {

template<typename T>
Tensor<T, 2> mult(Tensor<T, 2> a, Tensor<T, 2> b) {
    std::vector<T> data = std::vector<T>

    assert(a.n == b.m);
    for (int i=0; i<a.m; i++) {
        for (int j=0; j<b.n; j++) {
            // C_i,j
            T sum = T {};
            for(int k=0; k<a.n; k++) {
                sum += a._get_element(Tensor<T, 2>::_index_from_indices({i, k})) * b._get_element(Tensor<T, 2>::_index_from_indices({k, j}));
            }
            data[_index_from_indices({i, j})] = sum;
        }
    }
}

} // namespace span