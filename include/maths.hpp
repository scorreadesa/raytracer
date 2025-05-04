#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cstdint>
#include <iostream>

namespace raytracer::maths {

    template<typename T>
    class Point3D {
    private:
        T x_, y_, z_, w_;
    public:
        Point3D(T x, T y, T z) : x_(x), y_(y), z_(z), w_(1) {}
        T x() const { return x_; }
        T y() const { return y_; }
        T z() const { return z_; }
        T w() const { return w_; }
        T& x() { return x_; }
        T& y() { return y_; }
        T& z() { return z_; }
        T& w() { return w_; }
        friend std::ostream& operator<<(std::ostream& os, const Point3D<T>& p) {
            os << "(" << p.x_ << ", " << p.y_ << ", " << p.z_ << ")";
            return os;
        }
    };

    template<typename T>
    class Vector3D {
    private:
        T x_, y_, z_, w_;
    public:
        Vector3D(T x, T y, T z) : x_(x), y_(y), z_(z), w_(0) {}
        T x() const { return x_; }
        T y() const { return y_; }
        T z() const { return z_; }
        T w() const { return w_; }
        T& x() { return x_; }
        T& y() { return y_; }
        T& z() { return z_; }
        T& w() { return w_; }
        friend std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v) {
            os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
            return os;
        }
    };

    template<std::floating_point T>
    bool AlmostEqualEpsilon(T a, T b, T tolerance = std::numeric_limits<T>::epsilon()) {
        return std::abs(a - b) < tolerance;
    }
}

#endif //GEOMETRY_H
