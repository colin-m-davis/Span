#pragma once

#include <vector>
#include <algorithm>

namespace span {

// Stops after reaching the end of one vector
template<typename T>
T dot_product(const std::vector<T>& v, const std::vector<T>& u) {
    T result{};
    for (auto it_v = v.begin(), it_u = u.begin(); it_v != v.end() && it_u != u.end(); ++it_v, ++it_u)
        result += *it_v * *it_u;
    return result;
}

} // namespace span
