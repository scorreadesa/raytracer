#ifndef RAY_HPP
#define RAY_HPP

#include <cmath>

#include "maths.hpp"

namespace raytracer::maths {
    template <std::floating_point T>
    class Ray {
    private:
        Point3D<T> origin_;
        Vector3D<T> direction_;

    public:
        Ray(const Point3D<T>& origin, const Vector3D<T> direction) : origin_(origin), direction_(direction) {}
        ~Ray() = default;

        decltype(origin_) origin() const {return origin_;}
        decltype(direction_) direction() const {return direction_;}

        Point3D<T> position(T t) const {
            auto dt = direction_ * t;
            auto new_pos = origin_ + dt;
            return new_pos;
        }
    };
}

#endif //RAY_HPP
