#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <cmath>
#include <memory>

#include "drawing.hpp"
#include "Point3D.hpp"

namespace raytracing::shading {

    template <std::floating_point T>
    class Light {
    public:
        virtual ~Light() = default;
        virtual raytracer::maths::Point3D<T> position() const = 0;
        virtual raytracer::drawing::Color<T> intensity() const = 0;
        virtual std::unique_ptr<Light<T>> clone() const = 0;
    };
}

#endif //LIGHT_HPP
