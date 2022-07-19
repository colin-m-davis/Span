#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <vector>
#include <cmath>

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

template<typename T>
T dot_product(const std::vector<T>& v, const std::vector<T>& u) {
    assert(v.size() == u.size());
    T s = T {};
    for (int i=0; i<v.size(); i++) {
        s = s + (v[i] * u[i]);
    }
    return s;
}

template<typename T>
T norm(const std::vector<T>& v) {
    return cmath::sqrt(dot_product(v, v));
}

} // namespace span

#endif /* VECTOR_HPP_ */

