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
};


template<typename T>
Matrix<T> Matrix<T>::mult(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a.n == b.m);

    Matrix<T> c({a.m, b.n});
    std::vector<T> data;

    for (int i=0; i<a.m; i++) {
        for (int j=0; j<b.n; j++) {
            // C_i,j
            T sum = T {};
            int a_index = a._index_from_indices({i, 0});
            int b_index = b._index_from_indices({0, j});
            for(int k=0; k<a.n; k++) {
                sum += a._get_element(a_index) * b._get_element(b_index);
                a_index++; // a._strides[1] = 1 for any a
                b_index+=b._strides[0];
            }
            c._data[c._index_from_indices({i, j})] = sum;
        }
    }
    return c;
}

/*

*/

} // namespace span