/* For testing purposes */

#include "tensor.h"
#include <iostream>

int main() {
    std::vector<std::vector<std::vector<std::vector<int> > > > Matrix =
{
    {
        {
            {10, 5, -3},
            {1, 2, 3},
            {5, 6, 9}
        },
        {
            {10, 5, -3},
            {1, 2, 3},
            {5, 6, 9}
        }, 
        {
            {10, 5, -3},
            {1, 2, 3},
            {5, 6, 9}
        }
    },
    {
        {
            {10, 5, -3},
            {1, 2, 3},
        },
        {
            {10, 5, -3},
            {1, 2, 3},
            {5, 6, 9}
        }, 
        {
            {10, 5, -3}
        }
    }
};
    std::vector<size_t> deep = {};
    span::get_shape(Matrix, deep);
    std::vector<int> out;
    span::flatten(Matrix, out);
L}

