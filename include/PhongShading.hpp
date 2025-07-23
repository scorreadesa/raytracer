#ifndef PHONGSHADING_HPP
#define PHONGSHADING_HPP

#include "Shading.hpp"
#include "Vector3D.hpp"

namespace raytracer::shading {
    template <std::floating_point T>
    class PhongShading final : public Shading<T> {
    public:
        drawing::Color<T> shade(
            const Material<T> &material,
            const PointLight<T> &point_light,
            const maths::Point3D<T> &position,
            const maths::Vector3D<T> &eye,
            const maths::Vector3D<T> &normal
        ) const override {

            const auto effective_color = material.color_ * point_light.intensity_;
            auto lightv = normalize(point_light.position_ - position);
            const auto ambient = effective_color * material.ambient_;
            const auto light_dot_normal = dot(lightv, normal);

            auto diffuse = drawing::Color<T>(0, 0, 0);
            auto specular = drawing::Color<T>(0, 0, 0);

            if (light_dot_normal < static_cast<T>(0)) {
                diffuse = drawing::Color<T>(0, 0, 0);
                specular = drawing::Color<T>(0, 0, 0);
            } else {
                diffuse = effective_color * material.diffuse_ * light_dot_normal;
                const auto reflectv = maths::reflect(-lightv, normal);
                const auto reflect_dot_eye = dot(reflectv, eye);

                if (reflect_dot_eye <= static_cast<T>(0)) {
                    specular = drawing::Color<T>(0.0, 0.0, 0.0);
                } else {
                    const auto factor = std::pow(reflect_dot_eye, material.shininess_);
                    specular = point_light.intensity_ * material.specular_ * factor;
                }
            }

            return ambient + diffuse + specular;
        }
    };
}

#endif //PHONGSHADING_HPP
