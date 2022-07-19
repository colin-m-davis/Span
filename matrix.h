#include "tensor.h"


namespace span {

/*
Matrix class
For the purpose of this library, a matrix is a rank 2 tensor.
Mathematicians and physicists, lower your pitchforks please!!!
*/
template<typename T>
class Matrix : public Tensor<T, 2> {

public:
    int m; // # rows
    int n; // # columns

    Matrix(std::array<T, 2> shape) : Tensor<T, 2>(shape) {
        m = shape[0]; 
        n = shape[1];
    }

    /*
    Row echelon form
    TODO: definition (prerequisite: select/view)
    */
    Matrix<T> get_ref(const Matrix<T>& a);

    /*
    Matrix multiplication (naive implementation)
    https://en.wikipedia.org/wiki/Matrix_multiplication
    Mapping to and from linear data storage and row, column notation is expensive for small matrices but negligible
    in comparison to the efficiency gained by storing large objects linearly in memory.
    */
    static Matrix<T> mult(const Matrix<T>& a, const Matrix<T>& b);

    /*
    Naive, out-of-place matrix transpose
    TODO: cache efficient (cache oblivious, even) algorithm for large matrices
    https://en.wikipedia.org/wiki/Cache-oblivious_algorithm
    */
    static Matrix<T> transpose(const Matrix<T>& a);
};


template<typename T>
Matrix<T> Matrix<T>::mult(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.n == b.m);

    Matrix<T> c({a.m, b.n});

    for (int i=0; i<a.m; i++) {
        for (int j=0; j<b.n; j++) {
            // C_i,j

            // Initialize object to default
            T sum = T {};

            // i-th row of a, j-th column of b
            int a_index = a._index_from_indices({i, 0});
            int b_index = b._index_from_indices({0, j});
            for(int k=0; k<a.n; k++) {
                sum += a._get_element(a_index) * b._get_element(b_index);
                a_index++; // For all M, M._strides[1] == 1 
                b_index+=b.n; // For all M, M._strides[0] == M.n
            }
            c._data[c._index_from_indices({i, j})] = sum;
        }
    }
    return c;
}

template<typename T>
Matrix<T> Matrix<T>::transpose(const Matrix<T>& a) {
    Matrix<T> b({a.n, a.m}); // Transpose of m x n matrix is n x m matrix
    for (int i=0; i<b.m; i++) {
        for (int j=0; j<b.n; j++) {
            T element = a._get_element({j, i});
            b._set_element({i, j}, element);
        }
    }
    return b;
}

/*

*/



} // namespace span