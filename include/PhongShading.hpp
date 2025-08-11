#ifndef PHONGSHADING_HPP
#define PHONGSHADING_HPP

#include "PhongMaterial.hpp"
#include "Shading.hpp"
#include "Vector3D.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    class PhongShading final : public Shading<T> {
    public:

        [[nodiscard]] ShadingModel model() const override {
            return ShadingModel::Phong;
        }

        drawing::Color<T> shade(
            const ShadingContext<T> &context
        ) const override {

            const auto& phong_material = static_cast<const PhongMaterial<T>&>(context.material_);

            const auto effective_color = phong_material.color_ * context.light_.intensity();
            auto lightv = normalize(context.light_.position() - context.position_);
            const auto ambient = effective_color * phong_material.ambient_;
            const auto light_dot_normal = dot(lightv, context.normal_);

            auto diffuse = drawing::Color<T>(0, 0, 0);
            auto specular = drawing::Color<T>(0, 0, 0);

            if (light_dot_normal < static_cast<T>(0)) {
                diffuse = drawing::Color<T>(0, 0, 0);
                specular = drawing::Color<T>(0, 0, 0);
            } else {
                diffuse = effective_color * phong_material.diffuse_ * light_dot_normal;
                const auto reflectv = maths::reflect(-lightv, context.normal_);
                const auto reflect_dot_eye = dot(reflectv, context.eye_);

                if (reflect_dot_eye <= static_cast<T>(0)) {
                    specular = drawing::Color<T>(0.0, 0.0, 0.0);
                } else {
                    const auto factor = std::pow(reflect_dot_eye, phong_material.shininess_);
                    specular = context.light_.intensity() * phong_material.specular_ * factor;
                }
            }

            return ambient + diffuse + specular;
        }
    private:
        PhongMaterial<T> phong_material_;
    };
}

#endif //PHONGSHADING_HPP
