#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector3D.hpp"
#include "Exceptions.hpp"
#include <vector>
#include <iomanip>
#include <cmath>

namespace raytracer::maths {

    template<std::floating_point T>
    class Matrix {
    private:
        std::vector<T> data_;
        std::size_t rows_, cols_;

        void handle_shape_mismatch(const Matrix<T> &rhs) const noexcept(false) {
            if (this->rows_ != rhs.rows_ || this->cols_ != rhs.cols_) {
                auto err_msg_mismatch = "Shape mismatch: lhs has shape (" + std::to_string(this->rows_) + ","
                                        + std::to_string(this->cols_) + ") but rhs has shape (" + std::to_string(
                                            rhs.rows_)
                                        + "," + std::to_string(rhs.cols_) + ")";
                throw exceptions::ShapeMismatchException(err_msg_mismatch);
            }
        }

    public:
        Matrix(const std::size_t rows, const std::size_t cols) : data_(rows * cols, 0), rows_(rows), cols_(cols) {
        }

        Matrix(const std::size_t rows, const std::size_t cols,
               const std::initializer_list<T> &data) noexcept(false) : data_(data), rows_(rows), cols_(cols) {
            if ((rows_ * cols_) != data_.size()) {
                const auto err_msg_mismatch = "Shape mismatch: given storage size is " + std::to_string(rows_ * cols_)
                                              + ", but should be " + std::to_string(data_.size());
                throw exceptions::ShapeMismatchException(err_msg_mismatch);
            }
        }

        Matrix(const std::size_t rows, const std::size_t cols, const std::vector<T> &data) : data_(data), rows_(rows),
            cols_(cols) {
            if ((rows_ * cols_) != data.size()) {
                const auto err_msg_mismatch = "Shape mismatch: given storage size is " + std::to_string(rows_ * cols_)
                                              + ", but should be " + std::to_string(data_.size());
                throw exceptions::ShapeMismatchException(err_msg_mismatch);
            }
        }

        constexpr const T &operator()(const std::size_t row, const std::size_t col) const noexcept(false) {
            const auto err_msg_row = "Row index out of range: "
                                     + std::to_string(row) + " (valid range 0 <= row <" + std::to_string(rows_) + ")";
            if (row >= rows_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            const auto err_msg_col = "Col index out of range: "
                                     + std::to_string(col) + " (valid range 0 <= col < " + std::to_string(cols_) + ")";
            if (col >= cols_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return data_.at(row * cols_ + col);
        }

        constexpr T &operator()(const std::size_t row, const std::size_t col) noexcept(false) {
            const auto err_msg_row = "Row index out of range: "
                                     + std::to_string(row) + " (valid range 0 <= row < " + std::to_string(rows_) + ")";
            if (row >= rows_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            const auto err_msg_col = "Col index out of range: "
                                     + std::to_string(col) + " (valid range 0 <= col < " + std::to_string(cols_) + ")";
            if (col >= cols_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return data_.at(row * cols_ + col);
        }

        static Matrix<T> identity(const std::size_t size) {
            Matrix<T> m(size, size);
            for (std::size_t i = 0; i < size; i++) {
                m(i, i) = T{1};
            }
            return m;
        }

        friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
            std::vector<std::size_t> col_widths(m.data_.size(), 0);

            for (std::size_t j = 0; j < m.data_.size(); ++j) {
                std::size_t width = std::to_string(m.data_.at(j)).size();
                col_widths.at(j) = std::max(col_widths.at(j), width);
            }

            os << "[\n";
            for (std::size_t i = 0; i < m.rows_; i++) {
                os << "  [";
                for (std::size_t j = 0; j < m.cols_; j++) {
                    os << std::setw(col_widths.at(j)) << m(i, j);
                    if (j != m.cols_ - 1) {
                        os << ",";
                    }
                }
                os << "]";
                if (i != m.rows_ - 1) {
                    os << ",\n";
                } else {
                    os << "\n]";
                }
            }
            return os;
        }

        friend Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            lhs.handle_shape_mismatch(rhs);
            Matrix<T> result(lhs.rows_, rhs.cols_);
            for (std::size_t i = 0; i < lhs.rows_ * lhs.cols_; i++) {
                result.data_.at(i) = lhs.data_.at(i) + rhs.data_.at(i);
            }
            return result;
        }

        friend Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            lhs.handle_shape_mismatch(rhs);
            Matrix<T> result(lhs.rows_, rhs.cols_);
            for (std::size_t i = 0; i < lhs.rows_ * lhs.cols_; i++) {
                result.data_.at(i) = lhs.data_.at(i) - rhs.data_.at(i);
            }
            return result;
        }

        friend Matrix<T> operator*(const Matrix<T> &lhs, T scalar) {
            Matrix<T> result(lhs.rows_, lhs.cols_);
            for (std::size_t i = 0; i < lhs.rows_ * lhs.cols_; i++) {
                result.data_.at(i) = lhs.data_.at(i) * scalar;
            }
            return result;
        }

        friend Matrix<T> operator*(T scalar, const Matrix<T> &rhs) {
            Matrix<T> result(rhs.rows_, rhs.cols_);
            for (std::size_t i = 0; i < rhs.rows_ * rhs.cols_; i++) {
                result.data_.at(i) = rhs.data_.at(i) * scalar;
            }
            return result;
        }

        friend Matrix<T> matmul(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            if (lhs.cols_ != rhs.rows_) {
                lhs.handle_shape_mismatch(rhs);
            }
            Matrix<T> result(lhs.rows_, rhs.cols_);

            for (std::size_t i = 0; i < lhs.rows_; i++) {
                for (std::size_t j = 0; j < rhs.cols_; j++) {
                    T sum = 0;
                    for (std::size_t k = 0; k < lhs.cols_; k++) {
                        sum += lhs(i, k) * rhs(k, j);
                    }
                    result(i, j) = sum;
                }
            }
            return result;
        }

        friend Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs) {
            return matmul(lhs, rhs);
        }

        friend Matrix<T> operator/(const Matrix<T> &lhs, T scalar) {
            if (scalar == 0.0) {
                throw std::invalid_argument("division by zero");
            }
            Matrix<T> result(lhs.rows_, lhs.cols_);
            for (std::size_t i = 0; i < lhs.rows_ * lhs.cols_; i++) {
                result.data_.at(i) = lhs.data_.at(i) / scalar;
            }
            return result;
        }

        friend Matrix<T> transpose(const Matrix<T> &m) {
            auto result = Matrix<T>(m.cols_, m.rows_);

            for (std::size_t i = 0; i < m.rows_; i++) {
                for (std::size_t j = 0; j < m.cols_; j++) {
                    result(j, i) = m(i, j);
                }
            }

            return result;
        }

        void transpose() {
            auto result = Matrix<T>(cols_, rows_);

            for (std::size_t i = 0; i < rows_; i++) {
                for (std::size_t j = 0; j < cols_; j++) {
                    result(j, i) = data_.at(i * cols_ + j);
                }
            }

            std::swap(rows_, cols_);

            data_ = result.data_;
        }

        Matrix<T> &operator+=(const Matrix<T> &rhs) {
            handle_shape_mismatch(rhs);
            for (std::size_t i = 0; i < rows_ * cols_; i++) {
                data_.at(i) += rhs.data_.at(i);
            }
            return *this;
        }

        Matrix<T> &operator-=(const Matrix<T> &rhs) {
            handle_shape_mismatch(rhs);
            for (std::size_t i = 0; i < rows_ * cols_; i++) {
                data_.at(i) -= rhs.data_.at(i);
            }
            return *this;
        }

        Matrix<T> &operator*=(T scalar) {
            for (std::size_t i = 0; i < rows_ * cols_; i++) {
                data_.at(i) *= scalar;
            }
            return *this;
        }

        Matrix<T> &operator*=(const Matrix<T> &rhs) {
            auto ret = matmul(*this, rhs);
            data_ = ret.data_;
            cols_ = rhs.cols_;
            return *this;
        }

        Matrix<T> &operator/=(T scalar) {
            if (scalar == 0.0) {
                throw std::invalid_argument("division by zero");
            }
            for (std::size_t i = 0; i < rows_ * cols_; i++) {
                data_.at(i) /= scalar;
            }
            return *this;
        }

        void extend_row(const Matrix<T> &m) {
            if (cols_ != m.cols_) {
                auto err_msg_col = "Shape mismatch: lhs has " + std::to_string(cols_) + " columns but rhs has "
                                   + std::to_string(m.cols_) + " columns.";
                throw exceptions::ShapeMismatchException(err_msg_col);
            }

            data_.insert(data_.end(), m.data_.begin(), m.data_.end());
            rows_ += m.rows_;
        }

        void extend_col(const Matrix<T> &m) {
            if (rows_ != m.rows_) {
                auto err_msg_rows = "Shape mismatch: lhs has " + std::to_string(rows_) + " rows but rhs has "
                                    + std::to_string(m.rows_) + " rows.";
                throw exceptions::ShapeMismatchException(err_msg_rows);
            }

            auto new_data = std::vector<T>(rows_ * (cols_ + m.cols_));
            const std::size_t new_col = cols_ + m.cols_;

            for (std::size_t i = 0; i < rows_; i++) {
                // std::size_t new_col_idx = 0;
                for (std::size_t j = 0; j < new_col; j++) {
                    if (j < cols_) {
                        new_data.at(i * new_col + j) = data_.at(i * cols_ + j);
                    } else {
                        new_data.at(i * new_col + j) = m.data_.at(i * m.cols() + j - cols_);
                        // ++new_col_idx;
                    }
                }
            }

            data_ = new_data;
            cols_ = new_col;
        }

        [[nodiscard]] std::size_t rows() const noexcept { return rows_; }
        [[nodiscard]] std::size_t cols() const noexcept { return cols_; }
    };

    template<std::floating_point T>
    Matrix<T> submatrix(const Matrix<T> &matrix, const std::size_t row, const std::size_t col) {
        const auto m_rows = matrix.rows();
        const auto m_cols = matrix.cols();

        if (row >= matrix.rows()) {
            auto msg = "Cannot remove row " + std::to_string(row) + " from matrix with shape ("
                       + std::to_string(m_rows) + ", " + std::to_string(m_cols) + ").";
            throw exceptions::RowOutOfRangeException(msg);
        }

        if (col >= matrix.cols()) {
            auto msg = "Cannot remove col " + std::to_string(col) + " from matrix with shape ("
                       + std::to_string(m_rows) + ", " + std::to_string(m_cols) + ").";
            throw exceptions::ColumnOutOfRangeException(msg);
        }

        std::vector < T > data;
        for (std::size_t i = 0; i < m_rows; i++) {
            if (i != row) {
                for (std::size_t j = 0; j < m_cols; j++) {
                    if (j != col) {
                        data.push_back(matrix(i, j));
                    }
                }
            }
        }

        auto m = Matrix<T>(m_rows - 1, m_cols - 1, data);

        return m;
    }

    template<std::floating_point T>
    Vector3D<T> vector_from_row_matrix(const Matrix<T> &matrix) {
        return Vector3D<T>(
            matrix(0, 0),
            matrix(0, 1),
            matrix(0, 2)
        );
    }
}

#endif //MATRIX_HPP
