#ifndef TENSOR_H_
#define TENSOR_H_

// Dependencies
#include <stdlib.h>
#include <vector>

namespace span {

// n-dimensional vector
template<typename T>
class Tensor {
    int _size = 1;
    int n;
    std::vector<int> shape;
    std::vector<int> _strides;
    std::vector<T> _data; 
    
    Tensor(std::vector<int> s, std::vector<T> d);

    void _set_shape(std::vector<int> s);

    int _index_from_indices(const std::vector<int>& indices);

    std::vector<int> _indices_from_index(int index);

    T _get_element(const std::vector<int>& indices);

    T _get_element(int index_of_element);

    void _set_element(const std::vector<int>& indices, T element);

    void _set_element(int index_of_element, T element);

    // Add each of this element to that element and return new tensor
    Tensor<T> operator+ (Tensor<T> const& that);

    // Subtract each of this element from that element and return new tensor
    Tensor<T> operator- (Tensor<T> const& that);

    bool operator== (Tensor<T> const& that);
};

/* -----------------------
BEGIN IMPLEMENTATION
------------------------*/

template<typename T>
Tensor<T>::Tensor(std::vector<int> s, std::vector<T> d) {
    _set_shape(s);
    _data = d;
}

template<typename T>
void Tensor<T>::_set_shape(std::vector<int> s) {
    shape = s;
    n = shape.size();
    _strides.resize(n);
    for (int i=n-1; i>=0; i--) {
        _size *= shape[i];
        _strides[i] = (i == n-1) ? (1) : (shape[i+1] * _strides[i+1]);
    }
    _data.reserve(_size);
}

template<typename T>
int Tensor<T>::_index_from_indices(const std::vector<int>& indices) {
    int index = 0;
    for (int i=0; i<indices.size(); i++) {
        index += indices[i] * _strides[i];
    }
    return index;
}

template<typename T>
std::vector<int> Tensor<T>::_indices_from_index(int index) {
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

template<typename T>
T Tensor<T>::_get_element(const std::vector<int>& indices) {
    int index_of_element = _index_from_indices(indices);
    return _data[index_of_element];
}

template<typename T>
T Tensor<T>::_get_element(int index_of_element) {
    return _data[index_of_element];
}

template<typename T>
void Tensor<T>::_set_element(const std::vector<int>& indices, T element) {
    int index_of_element = _index_from_indices(indices);
    _data[index_of_element] = element;
}

template<typename T>
void Tensor<T>::_set_element(int index_of_element, T element) {
    _data[index_of_element] = element;
}

// Add each of this element to that element and return new tensor
template<typename T>
Tensor<T> Tensor<T>::operator+ (Tensor<T> const& that) {
    Tensor<T> result(shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]+that._data[i]);
    }
    return result;
}

// Subtract each of this element from that element and return new tensor
template<typename T>
Tensor<T> Tensor<T>::operator- (Tensor<T> const& that) {
    Tensor<T> result(shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]-that._data[i]);
    }
    return result;
}

template<typename T>
bool Tensor<T>::operator== (Tensor<T> const& that) {
    return ((shape = that.shape) & (_data = that.data));
}

#endif // TENSOR_H_

} // namespace span