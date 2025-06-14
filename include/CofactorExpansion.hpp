//
// Created by antares on 11.06.25.
//

#ifndef COFACTORSOLVER_HPP
#define COFACTORSOLVER_HPP

#include "Solver.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class CofactorExpansion final : public Solver<T> {
    public:
        T determinant(const Matrix<T> &m) const override {
            if (m.rows() == 2 and m.cols() == 2) {
                return m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
            }

            T det{0};
            for (std::size_t col = 0; col < m.cols(); ++col) {
                det = det + m(0, col) * cofactor(m, 0, col);
            }

            return det;
        }

        T minor(const Matrix<T> &m, const std::size_t row, const std::size_t col) const {
            const auto sub_matrix = submatrix(m, row, col);
            return determinant(sub_matrix);
        }

        T cofactor(const Matrix<T> &m, const std::size_t row, const std::size_t col) const {
            const auto submat_minor = minor(m, row, col);
            const size_t sum_row_col = row + col;
            return (sum_row_col % 2 == 0) ? submat_minor : -submat_minor;
        }

        Matrix<T> inverse(const Matrix<T> &m) const override {
            return Matrix<T>(1, 1, {0, 0});
        }
    };
}

#endif //COFACTORSOLVER_HPP
