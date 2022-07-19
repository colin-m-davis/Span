#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <vector>
#include <cmath>

namespace span {

/* fr */
template<typename T>
T dot_product(std::vector<T> v, std::vector<T> u);

template<typename T>
T norm(std::vector<T> v);

} // namespace span

#endif /* VECTOR_HPP_ */

