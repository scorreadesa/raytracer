#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <memory>
#include "Matrix.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class Solver {
    public:
        Solver() = default;
        virtual ~Solver() = default;

        Solver(const Solver&) = delete;
        Solver& operator=(const Solver&) = delete;
        Solver(Solver&&) = delete;
        Solver& operator=(Solver&&) = delete;


        virtual T determinant(const Matrix<T> &m) const = 0;

        virtual Matrix<T> inverse(const Matrix<T> &m) const = 0;
    };
}

#endif //SOLVER_HPP
