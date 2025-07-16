#ifndef POINT3D_HPP
#define POINT3D_HPP

namespace raytracer::maths {

    template <std::floating_point T>
    class Vector3D;

    template <std::floating_point T>
    class Matrix;

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

        friend Point3D<T> operator+(const Point3D<T> &lhs, const Vector3D<T> &rhs) {
            return Point3D<T>(lhs.x_ + rhs.x(), lhs.y_ + rhs.y(), lhs.z_ + rhs.z());
        }

        friend Point3D<T> operator+(const Vector3D<T> &lhs, const Point3D<T> &rhs) {
            return Point3D(rhs.x_ + lhs.x(), rhs.y_ + lhs.y(), rhs.z_ + lhs.z());
        }

        friend Vector3D<T> operator-(const Point3D<T> &lhs, const Point3D<T> &rhs) {
            return Vector3D<T>(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_, lhs.z_ - rhs.z_);
        }

        friend Point3D<T> operator-(const Point3D<T> &lhs, const Vector3D<T> &rhs) {
            return Point3D<T>(lhs.x_ - rhs.x(), lhs.y_ - rhs.y(), lhs.z_ - rhs.z());
        }

        friend Point3D<T> operator*(const Matrix<T> &m, const Point3D<T> &rhs) {
            T nx = m(0, 0) * rhs.x() + m(0, 1) * rhs.y() + m(0, 2) * rhs.z() + m(0, 3);
            T ny = m(1, 0) * rhs.x() + m(1, 1) * rhs.y() + m(1, 2) * rhs.z() + m(1, 3);
            T nz = m(2, 0) * rhs.x() + m(2, 1) * rhs.y() + m(2, 2) * rhs.z() + m(2, 3);
            T nw = m(3, 0) * rhs.x() + m(3, 1) * rhs.y() + m(3, 2) * rhs.z() + m(3, 3);
            return Point3D<T>(nx, ny, nz);
        }

        friend Point3D<T> operator*(T scalar, const Point3D<T>& rhs) {
            return Point3D<T>(scalar * rhs.x_, scalar * rhs.y_, scalar * rhs.y_);
        }

        friend Point3D<T> operator*(const Point3D<T>& lhs, T scalar) {
            return Point3D<T>(lhs.x_ * scalar, lhs.y_ * scalar, lhs.z_ * scalar);
        }
    };
}

#endif //POINT3D_HPP
