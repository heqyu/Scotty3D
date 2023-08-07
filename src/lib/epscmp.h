#pragma once

#define Math_Epsilon 0.00001f

namespace eps {


template<typename T> inline bool approx_equal(T a, T b) { return std::abs(a - b) < Math_Epsilon; }

template<typename T, unsigned int size> inline bool approx_equal(const T* a, const T* b) {
    for(unsigned int i = 0; i < size; ++i) {
        if(approx_equal(a[i], b[i]) == false) {
            return false;
        }
    }
    return true;
}

template<typename T> inline void eps_correct(T& a) {
    T floor = std::floor(a);
    T ceil = std::ceil(a);
    if(std::abs(a - floor) < Math_Epsilon) {
        a = floor;
    } else if(std::abs(a - ceil) < Math_Epsilon) {
        a = ceil;
    }
}

template<typename T, unsigned int size> inline void eps_correct(T (&a)[size]) {
    for(unsigned int i = 0; i < size; ++i) {
        eps_correct(a[i]);
    }
}


}; // namespace eps
