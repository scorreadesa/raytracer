#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Shading.hpp"
#include "Ray.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    class Shape;

    template<std::floating_point T>
    struct Intersection {
        T t_;
        const Shape<T> *shape_;

        Intersection(T t, const Shape<T> *shape) : t_(t), shape_(shape) {
        }

        Intersection(const Intersection &) = default;

        Intersection(Intersection &&) = default;

        Intersection &operator=(const Intersection &) = default;

        Intersection &operator=(Intersection &&) = default;

        bool operator<(const Intersection<T> &intersection) const {
            return t_ < intersection.t_;
        }
    };

    template<std::floating_point T>
    bool operator<(const Intersection<T> &lhs, const Intersection<T> &rhs) {
        return lhs.t_ < rhs.t_;
    }

    template<std::floating_point T>
    class Shape {
    public:
        Shape() : transform_(maths::Matrix<T>::identity(4)), material_(std::make_shared<shading::PhongMaterial<T> >()) {
        }

        explicit Shape(const maths::Matrix<T> &transform) : transform_(transform),
                                                            material_(std::make_shared<shading::PhongMaterial<T> >()) {
        }

        Shape(const maths::Matrix<T> &transform,
              const std::shared_ptr<shading::Material<T> > &material) : transform_(transform),
                                                                        material_(material) {
        }

        explicit Shape(const std::shared_ptr<shading::Material<T> > &material) : transform_(maths::Matrix<T>::identity(
                4)),
            material_(material) {
        }

        virtual ~Shape() = default;

        virtual std::vector<Intersection<T> > intersect(const maths::Ray<T> &ray) const = 0;

        virtual maths::Vector3D<T> normal_at(const maths::Point3D<T> &world_point) const = 0;

        virtual std::unique_ptr<Shape<T> > clone() const = 0;

        maths::Matrix<T> transform() const { return transform_; }
        std::shared_ptr<shading::Material<T> > material() const { return material_; }

        void set_transform(const maths::Matrix<T> &transform) { transform_ = transform; }
        void set_material(const shading::Material<T> &material) { material_ = material; }

    private:
        maths::Matrix<T> transform_;
        std::shared_ptr<shading::Material<T> > material_;
    };
}

#endif //SHAPE_HPP
