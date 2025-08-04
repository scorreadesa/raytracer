#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <cmath>

namespace raytracer::shading {
    enum class ShadingModel {
        Phong,
    };

    template<std::floating_point T>
    struct Material {
        virtual ~Material() = default;

        [[nodiscard]] virtual ShadingModel model() const = 0;
    };
}


#endif //MATERIAL_HPP
