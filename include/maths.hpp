#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath>
#include <iomanip>
#include <vector>
#include "exceptions.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class Vector3D {
    private:
        T x_, y_, z_, w_;

    public:
        Vector3D(T x, T y, T z) : x_(x), y_(y), z_(z), w_(0) {
        }

        T x() const { return x_; }
        T y() const { return y_; }
        T z() const { return z_; }
        T w() const { return w_; }

        T &x() { return x_; }
        T &y() { return y_; }
        T &z() { return z_; }
        T &w() { return w_; }

        friend std::ostream &operator<<(std::ostream &os, const Vector3D<T> &v) {
            os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
            return os;
        }

        friend Vector3D<T> operator+(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
            return Vector3D<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_, lhs.z_ + rhs.z_);
        }

        friend Vector3D<T> operator-(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
            return Vector3D(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
        }

        friend Vector3D<T> operator*(const Vector3D<T> &lhs, T scalar) {
            return Vector3D<T>(scalar * lhs.x_, scalar * lhs.y_, scalar * lhs.z_);
        }

        friend Vector3D<T> operator*(T scalar, const Vector3D<T> &rhs) {
            return Vector3D<T>(scalar * rhs.x_, scalar * rhs.y_, scalar * rhs.z_);
        }

        friend Vector3D<T> operator/(const Vector3D<T> &lhs, T scalar) {
            return Vector3D<T>(lhs.x_ / scalar, lhs.y_ / scalar, lhs.z_ / scalar);
        }

        Vector3D<T> &operator+=(const Vector3D<T> &rhs) {
            x_ += rhs.x_;
            y_ += rhs.y_;
            z_ += rhs.z_;
            return *this;
        }

        Vector3D<T> &operator-=(const Vector3D<T> &rhs) {
            x_ -= rhs.x_;
            y_ -= rhs.y_;
            z_ -= rhs.z_;
            return *this;
        }

        Vector3D<T> &operator*=(T scalar) {
            x_ *= scalar;
            y_ *= scalar;
            z_ *= scalar;
            return *this;
        }

        Vector3D<T> &operator-() {
            x_ = -x_;
            y_ = -y_;
            z_ = -z_;
            return *this;
        }

        T length() const {
            return std::sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
        }

        void normalize() {
            auto l = length();
            x_ /= l;
            y_ /= l;
            z_ /= l;
        }


        friend Vector3D normalize(const Vector3D<T> &v) {
            auto l = v.length();
            return Vector3D(v.x_ / l, v.y_ / l, v.z_ / l);
        }

        T dot(const Vector3D<T> &rhs) const {
            return x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_;
        }


        friend T dot(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
            return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
        }

        Vector3D<T> cross(const Vector3D<T> &rhs) const {
            T a_1 = y_ * rhs.z_ - z_ * rhs.y_;
            T a_2 = z_ * rhs.x_ - x_ * rhs.z_;
            T a_3 = x_ * rhs.y_ - y_ * rhs.x_;
            return Vector3D<T>(a_1, a_2, a_3);
        }


        friend Vector3D<T> cross(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
            T a_1 = lhs.y_ * rhs.z_ - lhs.z_ * rhs.y_;
            T a_2 = lhs.z_ * rhs.x_ - lhs.x_ * rhs.z_;
            T a_3 = lhs.x_ * rhs.y_ - lhs.y_ * rhs.x_;
            return Vector3D<T>(a_1, a_2, a_3);
        }
    };

    template<std::floating_point T>
    class Point3D {
    private:
        T x_, y_, z_, w_;

    public:
        Point3D(T x, T y, T z) : x_(x), y_(y), z_(z), w_(1) {
        }

        T x() const { return x_; }
        T y() const { return y_; }
        T z() const { return z_; }
        T w() const { return w_; }

        T &x() { return x_; }
        T &y() { return y_; }
        T &z() { return z_; }
        T &w() { return w_; }

        friend std::ostream &operator<<(std::ostream &os, const Point3D<T> &p) {
            os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
            return os;
        }

        friend Point3D<T> operator+(const Point3D<T> &lhs, Vector3D<T> &rhs) {
            return Point3D<T>(lhs.x_ + rhs.x(), lhs.y_ + rhs.y(), lhs.z_ + rhs.z());
        }

        friend Point3D<T> operator+(const Vector3D<T> &lhs, Point3D<T> &rhs) {
            return Point3D(rhs.x_ + lhs.x(), rhs.y_ + lhs.y(), rhs.z_ + lhs.z());
        }

        friend Vector3D<T> operator-(const Point3D<T> &lhs, Point3D<T> &rhs) {
            return Vector3D<T>(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
        }

        friend Point3D<T> operator-(const Point3D<T> &lhs, Vector3D<T> &rhs) {
            return Point3D<T>(lhs.x_ - rhs.x(), lhs.y_ - rhs.y(), lhs.z_ - rhs.z());
        }
    };


    template<std::floating_point T>
    bool AlmostEqualEpsilon(T a, T b,
                            T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < tolerance;
    }

    template<std::floating_point T>
    T lerp(T v0, T v1, T t) {
        return (1 - t) * v0 + t * v1;
    }

    template<std::floating_point T>
    class Matrix {
    private:
        std::vector<T> data_;
        std::size_t rows_, cols_;

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

        constexpr const T &operator()(std::size_t row, std::size_t col) const noexcept(false) {
            const auto err_msg_row = "Row index out of range: "
                                     + std::to_string(row) + "(valid range 0 <= row <" + std::to_string(rows_) + ")";
            if (row >= rows_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            const auto err_msg_col = "Col index out of range: "
                                     + std::to_string(col) + "(valid range 0 <= col < " + std::to_string(cols_) + ")";
            if (col >= cols_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return data_[row * cols_ + col];
        }

        constexpr T &operator()(std::size_t row, std::size_t col) noexcept(false) {
            const auto err_msg_row = "Row index out of range: "
                                     + std::to_string(row) + "(valid range 0 <= row < " + std::to_string(rows_) + ")";
            if (row >= rows_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            const auto err_msg_col = "Col index out of range: "
                                     + std::to_string(col) + "(valid range 0 <= col < " + std::to_string(cols_) + ")";
            if (col >= cols_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return data_[row * cols_ + col];
        }

        static Matrix<T> identity(std::size_t size) {
            Matrix<T> m(size, size, {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            });
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
            if (lhs.rows_ != rhs.rows_ || lhs.cols_ != rhs.cols_) {
                auto err_msg_mismatch = "Shape mismatch: lhs has shape (" + std::to_string(lhs.rows_) + ","
                                        + std::to_string(lhs.cols_) + ") but rhs has shape (" + std::to_string(
                                            rhs.rows_)
                                        + "," + std::to_string(rhs.cols_) + ")";
                throw exceptions::ShapeMismatchException(err_msg_mismatch);
            }
            Matrix<T> result(lhs.rows_, rhs.cols_);
            for (std::size_t i = 0; i < lhs.rows_ * lhs.cols_; i++) {
                result.data_.at(i) = lhs.data_.at(i) + rhs.data_.at(i);
            }
            return result;
        }

        [[nodiscard]] std::size_t rows() const noexcept { return rows_; }
        [[nodiscard]] std::size_t cols() const noexcept { return cols_; }
    };
}

#endif //GEOMETRY_H
