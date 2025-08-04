#ifndef SHADING_HPP
#define SHADING_HPP

#include "drawing.hpp"
#include "PhongShading.hpp"
#include "Point3D.hpp"
#include "PointLight.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    class Shading;

    template<std::floating_point T>
    class PhongShading;

    template<std::floating_point T>
    struct Material {
        drawing::Color<T> color_;
        T ambient_;
        T diffuse_;
        T specular_;
        T shininess_;
        std::shared_ptr<Shading<T> > shading_;

        Material() = default;

        Material(const drawing::Color<T> &color, T ambient, T diffuse, T specular, T shininess)
            : color_(color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess),
              shading_(std::make_shared<PhongShading<T>>()) {
        }
    };

    template<std::floating_point T>
    struct ShadingContext {
        const Material<T>& material_;
        const Light<T>& light_;
        maths::Point3D<T> position_;
        maths::Vector3D<T> eye_;
        maths::Vector3D<T> normal_;

        ShadingContext() = delete;
        ShadingContext(const Material<T>& material, const Light<T>& light, const maths::Point3D<T>& position,
            const maths::Vector3D<T>& eye, const maths::Vector3D<T>& normal) :
        material_(material), light_(light), position_(position), eye_(eye), normal_(normal) {}
    };

    template<std::floating_point T>
    class Shading {
    public:
        virtual ~Shading() = default;

        virtual drawing::Color<T> shade(
            const ShadingContext<T>& context
        ) const = 0;
    };
}

#endif //SHADING_HPP
