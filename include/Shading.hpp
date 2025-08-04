#ifndef SHADING_HPP
#define SHADING_HPP

#include "drawing.hpp"
#include "PhongShading.hpp"
#include "Point3D.hpp"
#include "PointLight.hpp"
#include "Material.hpp"

namespace raytracer::shading {

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
