#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <cmath>
#include "Point3D.hpp"

namespace raytracer::maths {
    template<std::floating_point T>
    class Matrix;

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

        friend Vector3D<T> operator*(const Matrix<T> &m, const Vector3D<T> &rhs) {
            T nx = m(0, 0) * rhs.x() + m(0, 1) * rhs.y() + m(0, 2) * rhs.z() + m(0, 3) * rhs.w();
            T ny = m(1, 0) * rhs.x() + m(1, 1) * rhs.y() + m(1, 2) * rhs.z() + m(1, 3) * rhs.w();
            T nz = m(2, 0) * rhs.x() + m(2, 1) * rhs.y() + m(2, 2) * rhs.z() + m(2, 3) * rhs.w();
            return Vector3D<T>(nx, ny, nz);
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


        friend Vector3D<T> normalize(const Vector3D<T> &v) {
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
    Vector3D<T> reflect(const Vector3D<T> &in, const Vector3D<T> &normal) {
        return in - normal * 2 * dot(in, normal);
    }

    template<std::floating_point T>
    Matrix<T> vector_to_column_matrix(const Vector3D<T> &v) {
        return Matrix<T>(4, 1, {
                             v.x(), v.y(), v.z(), v.w()
                         });
    }

    template<std::floating_point T>
    Vector3D<T> vector_from_column_matrix(const Matrix<T> &matrix) {
        return Vector3D<T>(
            matrix(0, 0),
            matrix(1, 0),
            matrix(2, 0)
        );
    }


    template<std::floating_point T>
    Matrix<T> vector_to_row_matrix(const Vector3D<T> &v) {
        return Matrix<T>(1, 4, {
                             v.x(), v.y(), v.z(), v.w()
                         });
    }
}

#endif //VECTOR3D_HPP
