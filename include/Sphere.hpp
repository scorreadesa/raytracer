#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"
#include "maths.hpp"

namespace raytracer::scene {

    template <std::floating_point T>
    class Sphere final : public Shape<T> {
    public:
        using origin = maths::Point3D<T>;
        using intersections = std::vector<Intersection<T>>;
        Sphere() : origin_(origin(0, 0, 0)), radius_(1.0) {}
        Sphere(const origin& origin, T radius) : origin_(origin), radius_(radius) {}

        intersections intersect(const maths::Ray<T>& ray) const override {
            intersections xs;
            auto sphere_to_ray = ray.origin() - origin_;
            auto a = dot(ray.direction(), ray.direction());
            auto b = static_cast<T>(2) * dot(ray.direction(), sphere_to_ray);
            auto c = dot(sphere_to_ray, sphere_to_ray) - static_cast<T>(1);
            auto d = maths::discriminant(a, b, c);
            return xs;
        }

    private:
        maths::Point3D<T> origin_;
        T radius_;
    };
}

#endif //SPHERE_HPP
