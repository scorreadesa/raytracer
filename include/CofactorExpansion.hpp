#ifndef COFACTORSOLVER_HPP
#define COFACTORSOLVER_HPP

#include "Solver.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class CofactorExpansion final : public Solver<T> {
    public:
        T determinant(const Matrix<T> &m) const override {
            if (m.rows() == 1 and m.cols() == 1) {
                return m(0, 0);
            }

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
            auto det = determinant(m);
            // TODO: avoid equality comparisons when using floating point numbers
            if (det == 0) {
                const auto msg = "det(m) is zero, m is not invertible.";
                throw exceptions::NotInvertibleMatrixException(msg);
            }

            auto inverse = Matrix<T>(m.rows(), m.cols());

            for (std::size_t row = 0; row < m.rows(); ++row) {
                for (std::size_t col = 0; col < m.cols(); ++col) {
                    auto cf = cofactor(m, row, col);
                    inverse(col, row) = cf / det;
                }
            }
            return inverse;
        }

        std::unique_ptr<Solver<T>> clone() const override {
            return std::make_unique<CofactorExpansion<T>>(*this);
        }
    };
}

#endif //COFACTORSOLVER_HPP
