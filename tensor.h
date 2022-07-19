#ifndef TENSOR_H_
#define TENSOR_H_

// Dependencies
#include <stdlib.h>
#include <vector>
#include <array>

namespace span {

// n-dimensional array
template<typename T, int n>
class Tensor {

public: // TODO: more thoughtful access specifications to be implemented
    int _size = 1;
    int rank = n;
    std::array<int, n> _shape;
    std::array<int, n> _strides;
    std::vector<T> _data; 
    
    Tensor(std::array<int, n> s);

    void _set_shape(const std::array<int, n>& s);

    int _index_from_indices(const std::array<int, n>& indices);

    std::array<int, n> _indices_from_index(int index);

    T _get_element(const std::array<int, n>& indices);

    T _get_element(int index_of_element);

    void _set_element(const std::array<int, n>& indices, T element);

    void _set_element(int index_of_element, T element);

    // Add each of this element to that element and return new tensor
    Tensor<T, n> operator+ (Tensor<T, n> const& that);

    // Subtract each of this element from that element and return new tensor
    Tensor<T, n> operator- (Tensor<T, n> const& that);

    bool operator== (Tensor<T, n> const& that);
};

/* -----------------------
BEGIN IMPLEMENTATION
------------------------*/

template<typename T, int n>
Tensor<T, n>::Tensor(std::array<int, n> shape) {
    _set_shape(shape);
}

template<typename T, int n>
void Tensor<T, n>::_set_shape(const std::array<int, n>& shape) {
    _shape = shape;
    for (int i=n-1; i>=0; i--) {
        _size *= _shape[i];
        _strides[i] = (i == n-1) ? (1) : (_shape[i+1] * _strides[i+1]);
    }
    _data.resize(_size);
}

template<typename T, int n>
int Tensor<T, n>::_index_from_indices(const std::array<int, n>& indices) {
    int index = 0;
    for (int i=0; i<n; i++) {
        index += indices[i] * _strides[i];
    }
    return index;
}

template<typename T, int n>
std::array<int, n> Tensor<T, n>::_indices_from_index(int index) {
    std::vector<int> indices(n, 0);
    for (int i=0; i<n; i++) {
        int y = _strides[i];
        while (index >= y) {
            index -= y;
            indices[i]++;
        }
    }
    return indices;
}

template<typename T, int n>
T Tensor<T, n>::_get_element(const std::array<int, n>& indices) {
    int index_of_element = _index_from_indices(indices);
    return _data[index_of_element];
}

template<typename T, int n>
T Tensor<T, n>::_get_element(int index_of_element) {
    return _data[index_of_element];
}

template<typename T, int n>
void Tensor<T, n>::_set_element(const std::array<int, n>& indices, T element) {
    int index_of_element = _index_from_indices(indices);
    _data[index_of_element] = element;
}

template<typename T, int n>
void Tensor<T, n>::_set_element(int index_of_element, T element) {
    _data[index_of_element] = element;
}

// Add each of this element to that element and return new tensor
template<typename T, int n>
Tensor<T, n> Tensor<T, n>::operator+ (Tensor<T, n> const& that) {
    Tensor<T, n> result(_shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]+that._data[i]);
    }
    return result;
}

// Subtract each of this element from that element and return new tensor
template<typename T, int n>
Tensor<T, n> Tensor<T, n>::operator- (Tensor<T, n> const& that) {
    Tensor<T, n> result(_shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]-that._data[i]);
    }
    return result;
}

template<typename T, int n>
bool Tensor<T, n>::operator== (Tensor<T, n> const& that) {
    return ((_shape == that._shape) & (_data == that.data));
}

#endif // TENSOR_H_

} // namespace span