#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <vector>

namespace span {

/* fr */
template<typename T>
T dot_product(const std::vector<T>& v, const std::vector<T>& u);

/* for now, norm(v) == sqrt(dot_product(v, v)) */
template<typename T>
T norm(const std::vector<T>& v);

/* -----------------
BEGIN IMPLEMENTATION
----------------- */

} // namespace span

#endif /* VECTOR_HPP_ */

