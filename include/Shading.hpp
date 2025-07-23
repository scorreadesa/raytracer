#ifndef SHADING_HPP
#define SHADING_HPP

#include "drawing.hpp"
#include "Point3D.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    struct Material {
        drawing::Color<T> color_;
        T ambient_;
        T diffuse_;
        T specular_;
        T shininess_;

        Material() = default;

        Material(const drawing::Color<T> &color, T ambient, T diffuse, T specular, T shininess)
            : color_(color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess) {
        }
    };

    template<std::floating_point T>
    struct PointLight {
        maths::Point3D<T> position_;
        drawing::Color<T> intensity_;

        PointLight() = default;

        PointLight(const maths::Point3D<T> &position, const drawing::Color<T> &color)
            : position_(position), intensity_(color) {
        }
    };

    template<std::floating_point T>
    class Shading {
    public:
        virtual ~Shading() = default;

        virtual drawing::Color<T> shade(
            const Material<T> &material,
            const PointLight<T> &point_light,
            const maths::Point3D<T> &position,
            const maths::Vector3D<T> &eye,
            const maths::Vector3D<T> &normal
        ) const = 0;
    };
}

#endif //SHADING_HPP
