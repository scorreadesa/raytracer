#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "maths.hpp"
#include "Ray.hpp"

namespace raytracer::scene {
    template <std::floating_point T>
    class Shape;

    template <std::floating_point T>
    struct Intersection {
        T t_;
        const Shape<T>& shape_;
        Intersection(T t, const Shape<T>& shape) : t_(t), shape_(shape) {}
    };

    template <std::floating_point T>
    bool operator<(const Intersection<T>& lhs, const Intersection<T>& rhs) {
        return lhs.t_ < rhs.t_;
    }

    template <std::floating_point T>
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual std::vector<Intersection<T>> intersect(const maths::Ray<T>& ray) const = 0;
    };
}

#endif //SHAPE_HPP
