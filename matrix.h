#include "tensor.h"

// a series of operations available to Tensors of rank 2 (which I am equating to matrices for the purpose of this library)

namespace span {

template<typename T>
class Matrix : public Tensor<T, 2> {

public:
    int m; // # rows
    int n; // # columns

    Matrix(std::array<T, 2> shape) : Tensor<T, 2>(shape) {
        m = shape[0]; 
        n = shape[1];
    }

    
};

template<typename T>
Matrix<T> mult(Matrix<T> a, Matrix<T> b) {
    assert(a.n == b.m);

    Matrix<T> c({a.m, b.n});
    std::vector<T> data;

    for (int i=0; i<a.m; i++) {
        for (int j=0; j<b.n; j++) {
            // C_i,j
            T sum = T {};
            for(int k=0; k<a.n; k++) {
                sum += a._get_element(a._index_from_indices({i, k})) * b._get_element(b._index_from_indices({k, j}));
            }
            c._data[c._index_from_indices({i, j})] = sum;
        }
    }
    return c;
}

} // namespace span