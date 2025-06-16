#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <cmath>

#include "maths.hpp"
namespace raytracer::maths {
    template <std::floating_point T>
    class Transform4x4 {
    public:
        static Matrix<T> make_translation(T x, T y, T z) {
            return Matrix<T>(4, 4, {
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
            });
        }
    };
}

#endif //TRANSFORM_HPP
