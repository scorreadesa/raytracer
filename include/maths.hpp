#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <iomanip>
#include <vector>
#include "Exceptions.hpp"

namespace raytracer::maths {

    template<std::floating_point T>
    bool almost_equal_epsilon(T a, T b,
                              T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < tolerance;
    }

    template<std::floating_point T>
    T lerp(T v0, T v1, T t) {
        return (1 - t) * v0 + t * v1;
    }

    template <std::floating_point T>
    T deg2rad(T degrees) {
        return degrees * std::numbers::pi / 180.;
    }

    template <std::floating_point T>
    T rad2deg(T radians) {
        return radians * 180. / std::numbers::pi;
    }

    template <std::floating_point T>
    T discriminant(T a, T b, T c) {
        return std::pow(b, 2.0) - 4 * a * c;
    }

}

#endif //GEOMETRY_H
