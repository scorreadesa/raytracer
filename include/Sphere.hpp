#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"
#include "CofactorExpansion.hpp"
#include "Vector3D.hpp"
#include "Matrix.hpp"
#include "PhongMaterial.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    class Sphere final : public Shape<T> {
    public:
        using origin = maths::Point3D<T>;
        using intersections = std::vector<Intersection<T> >;

        Sphere() : Shape<T>(maths::Matrix<T>::identity(4), std::make_shared<shading::PhongMaterial<T> >()),
                   origin_(origin(0, 0, 0)),
                   radius_(1.0) {
        }

        Sphere(const origin &origin, T radius) : Shape<T>(maths::Matrix<T>::identity(4)), origin_(origin),
                                                 radius_(radius) {
        }

        explicit Sphere(const maths::Matrix<T> &transform) : Shape<T>(transform,
                                                                      std::make_shared<shading::PhongMaterial<T> >()),
                                                             origin_(origin(0, 0, 0)),
                                                             radius_(1.0) {
        }

        explicit Sphere(const std::shared_ptr<shading::Material<T> > &material) : Shape<T>(
                maths::Matrix<T>::identity(4), material),
            origin_(origin(0, 0, 0)), radius_(1.0) {
        }

        Sphere(const maths::Matrix<T> &transform,
               const std::shared_ptr<shading::Material<T> > &material) : Shape<T>(transform, material),
                                                                         origin_(origin(0, 0, 0)), radius_(1.0) {
        }

        Sphere(const origin &origin, T radius, const maths::Matrix<T> &transform) : Shape<T>(transform),
            origin_(origin), radius_(radius) {
        }

        intersections intersect(const maths::Ray<T> &ray) const override {
            auto inverse_transform = maths::CofactorExpansion<T>().inverse(this->transform());
            auto transformed_ray = maths::transform(ray, inverse_transform);

            auto sphere_to_ray = transformed_ray.origin() - origin_;
            auto a = dot(transformed_ray.direction(), transformed_ray.direction());
            auto b = static_cast<T>(2) * dot(transformed_ray.direction(), sphere_to_ray);
            auto c = dot(sphere_to_ray, sphere_to_ray) - static_cast<T>(1);
            auto d = maths::discriminant(a, b, c);

            intersections xs;

            if (d < 0) {
                return xs;
            }

            T t1 = (-b - std::sqrt(d)) / (static_cast<T>(2) * a);
            T t2 = (-b + std::sqrt(d)) / (static_cast<T>(2) * a);
            xs.emplace_back(t1, this);
            xs.emplace_back(t2, this);

            return xs;
        }

        maths::Vector3D<T> normal_at(const maths::Point3D<T> &world_point) const override {
            const auto solver = maths::CofactorExpansion<T>();
            const auto inverse_transform = solver.inverse(this->transform());

            const auto object_point = inverse_transform * world_point;
            const auto object_normal = object_point - origin_;
            auto world_normal = transpose(inverse_transform) * object_normal;
            world_normal.w() = static_cast<T>(0);
            return normalize(world_normal);
        }

        std::unique_ptr<Shape<T> > clone() const override {
            return std::make_unique<Sphere<T> >(*this);
        }

    private:
        maths::Point3D<T> origin_;
        T radius_;
    };
}

#endif //SPHERE_HPP
