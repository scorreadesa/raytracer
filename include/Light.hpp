#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <cmath>
#include <memory>

#include "drawing.hpp"
#include "Point3D.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    class Light {
    public:
        Light() = default;
        virtual ~Light() = default;

        Light(const Light&) = default;
        Light& operator=(const Light&) = default;
        Light(Light&&) = default;
        Light& operator=(Light&&) = default;


        virtual maths::Point3D<T> position() const = 0;

        virtual drawing::Color<T> intensity() const = 0;

        virtual std::unique_ptr<Light<T> > clone() const = 0;
    };
}

#endif //LIGHT_HPP
