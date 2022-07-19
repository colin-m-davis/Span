#ifndef TENSOR_HPP_
#define TENSOR_HPP_

// Dependencies
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

    int _index_from_indices(const std::array<int, n>& indices) const;
    std::array<int, n> _indices_from_index(int index) const;

    T _get_element(const std::array<int, n>& indices) const;
    T _get_element(int index_of_element) const;

    void _set_element(const std::array<int, n>& indices, T element);
    void _set_element(int index_of_element, T element);

    // Member method: slice/view
    // TODO: Implementation. trickier than i thought? or deceptively easy?
    // Return a new struct i.e. "Tensor view" or return a whole new tensor based on this slice?!

    // Add each of this element to that element and return new tensor
    Tensor<T, n> operator+ (const Tensor<T, n>& that);

    // Subtract each of this element from that element and return new tensor
    Tensor<T, n> operator- (const Tensor<T, n>& that);

    bool operator== (const Tensor<T, n>& that) const;
    bool operator!= (const Tensor<T, n>& that) const;
};

/* -----------------------
BEGIN IMPLEMENTATION
------------------------*/

template<typename T, int n>
Tensor<T, n>::Tensor(std::array<int, n> shape) {
    _shape = shape;
    for (int i=n-1; i>=0; i--) {
        _size *= _shape[i];
        _strides[i] = (i == n-1) ? (1) : (_shape[i+1] * _strides[i+1]); // Last stride is 1
    }
    _data.resize(_size);
}

template<typename T, int n>
int Tensor<T, n>::_index_from_indices(const std::array<int, n>& indices) const {
    int index = 0;
    for (int i=0; i<n; i++) {
        index += indices[i] * _strides[i];
    }
    return index;
}

template<typename T, int n>
std::array<int, n> Tensor<T, n>::_indices_from_index(int index) const {
    assert((index >= 0) && (index <= _size));
    std::vector<int> indices(n, 0);
    for (int i=0; i<n; i++) {
        indices[i] = index / _strides[i];
        index %= _strides[i];
    }
    return indices;
}

template<typename T, int n>
T Tensor<T, n>::_get_element(const std::array<int, n>& indices) const {
    int index_of_element = _index_from_indices(indices);
    return _data[index_of_element];
}

template<typename T, int n>
T Tensor<T, n>::_get_element(int index_of_element) const {
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
Tensor<T, n> Tensor<T, n>::operator+ (const Tensor<T, n>& that) {
    Tensor<T, n> result(_shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]+that._data[i]);
    }
    return result;
}

// Subtract each of this element from that element and return new tensor
template<typename T, int n>
Tensor<T, n> Tensor<T, n>::operator- (const Tensor<T, n>& that) {
    Tensor<T, n> result(_shape);
    for (int i=0; i<_size; i++) {
        result._set_element(i, _data[i]-that._data[i]);
    }
    return result;
}

template<typename T, int n>
bool Tensor<T, n>::operator== (const Tensor<T, n>& that) const {
    return ((_shape == that._shape) & (_data == that._data));
}

template<typename T, int n>
bool Tensor<T, n>::operator!= (const Tensor<T, n>& that) const {
    return (!(*this)==that);
}

} // namespace span

#endif // TENSOR_HPP_