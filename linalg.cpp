// #ifndef LINALG
// #define LINALG

// Dependencies
#include <stdlib.h>
#include <vector>
#include <numeric>
#include <exception>

// n-dimensional vector
template<typename T>
struct tensor {

    int _size = 1;
    int n;
    std::vector<int> dims;
    std::vector<int> _strides;
    std::vector<T> _data;

    tensor(std::vector<int> d) {
        dims = d;
        n = dims.size();
        _strides.resize(n);
        for (int i=n-1; i>=0; i--) {
            _size *= dims[i];
            _strides[i] = (i == n-1) ? (1) : (dims[i+1] * _strides[i+1]);
        }
        _data.reserve(_size);
    }

    int _index_from_indices(const std::vector<int>& indices) {
        int index = 0;
        for (int i=0; i<indices.size(); i++) {
            index += indices[i] * _strides[i];
        }
        return index;
    }

    std::vector<int> _indices_from_index(int index) {
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

    T _get_element(const std::vector<int>& indices) {
        int index_of_element = _index_from_indices(indices);
        return _data[index_of_element];
    }

    T _get_element(int index_of_element) {
        return _data[index_of_element];
    }

    void _set_element(const std::vector<int>& indices, T element) {
        int index_of_element = _index_from_indices(indices);
        _data[index_of_element] = element;
    }

    void _set_element(int index_of_element, T element) {
        _data[index_of_element] = element;
    }

    // Add each of this element to that element and return new tensor
    tensor<T> operator+ (tensor<T> const& that) {
        tensor<T> result(dims);
        for (int i=0; i<_size; i++) {
            result._set_element(i, _data[i]+that._data[i]);
        }
        return result;
    }

    // Increment each entry by a scalar
    tensor<T>* operator+ (float addend) {
        tensor<T> result(dims);
        for (int i=0; i<_size; i++) {
            result._set_element(i, _data[i]+addend);
        }
        return this;
    }

    // Subtract each of this element from that element and return new tensor
    tensor<T> operator- (tensor<T> const& that) {
        tensor<T> result(dims);
        for (int i=0; i<_size; i++) {
            result._set_element(i, _data[i]-that._data[i]);
        }
        return result;
    }

    // Decrement each entry by a scalar
    tensor<T>* operator- (float subtrahend) {
        tensor<T> result(dims);
        for (int i=0; i<_size; i++) {
            result._set_element(i, _data[i]-subtrahend);
        }
        return this;
    }

    // Multiply each entry by a scalar
    tensor<T>* operator* (float multiplier) {
        tensor<T> result(dims);
        for (int i=0; i<_size; i++) {
            result._set_element(i, _data[i]*multiplier);
        }
        return this;
    }

    bool operator== (tensor<T> const& that) {
        return ((dims = that.dims) & (_data = that.data));
    }
};



// #endif /* LINALG */