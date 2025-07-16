#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cmath>

#include "maths.hpp"
#include "Ray.hpp"

namespace raytracer::scene {

    template <std::floating_point T>
    struct Intersection {
        T t_;
    };

    template <std::floating_point T>
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual std::vector<Intersection<T>> intersect(const maths::Ray<T>& ray) const = 0;
    };
}

#endif //SHAPE_HPP
