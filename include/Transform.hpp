#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <cmath>

#include "maths.hpp"
namespace raytracer::maths {
    template <std::floating_point T>
    class Transform4x4 {
    public:
        static Matrix<T> translation(T x, T y, T z) {
            return Matrix<T>(4, 4, {
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
            });
        }
        static Matrix<T> scaling(T x, T y, T z) {
            return Matrix<T>(4, 4, {
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
            });
        }
        static Matrix<T> rotation_x(T radians) {
            return Matrix<T>(4, 4, {
                1, 0, 0, 0,
                0, std::cos(radians), -std::sin(radians), 0,
                0, std::sin(radians), std::cos(radians), 0,
                0, 0, 0, 1,
            });
        }
        static Matrix<T> rotation_y(T radians) {
            return Matrix<T>(4, 4, {
                std::cos(radians), 0, std::sin(radians), 0,
                0, 1, 0, 0,
                -std::sin(radians), 0, std::cos(radians), 0,
                0, 0, 0, 1,
            });
        }

        static Matrix<T> rotation_z(T radians) {
            return Matrix<T>(4, 4, {
                std::cos(radians), -std::sin(radians), 0, 0,
                std::sin(radians), std::cos(radians), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1,
            });
        }

        static Matrix<T> shearing(T xy, T xz, T yx, T yz, T zx, T zy) {
            return Matrix<T>(4, 4, {
                1, xy, xz, 0,
                yx, 1, yz, 0,
                zx, zy, 1, 0,
                0, 0, 0, 1
            });
        }
    };
}

#endif //TRANSFORM_HPP
