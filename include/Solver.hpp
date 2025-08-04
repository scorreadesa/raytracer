#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <cmath>
#include "maths.hpp"
#include "Matrix.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class Solver {
    public:
        virtual ~Solver() = default;

        virtual T determinant(const Matrix<T> &m) const = 0;

        virtual Matrix<T> inverse(const Matrix<T> &m) const = 0;
    };
}

#endif //SOLVER_HPP
