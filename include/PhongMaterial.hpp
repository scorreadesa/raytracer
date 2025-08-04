#ifndef PHONGMATERIAL_HPP
#define PHONGMATERIAL_HPP

#include "drawing.hpp"
#include "Material.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    struct PhongMaterial final : Material<T> {
        drawing::Color<T> color_;
        T ambient_;
        T diffuse_;
        T specular_;
        T shininess_;

        PhongMaterial() = default;

        PhongMaterial(const drawing::Color<T> &color, T ambient, T diffuse, T specular, T shininess)
            : color_(color), ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess){
        }

        [[nodiscard]] ShadingModel model() const override {
            return ShadingModel::Phong;
        }
    };
}

#endif //PHONGMATERIAL_HPP
