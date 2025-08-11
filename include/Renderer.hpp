#ifndef RENDERER_HPP
#define RENDERER_HPP
#include "PhongShading.hpp"
#include "Scene.hpp"

namespace raytracer::core {
    template<std::floating_point T>
    class Renderer {
    public:
        explicit Renderer(const scene::Scene<T> &scene) : scene_(scene) {
        }

        drawing::Color<T> shade_hit(const scene::IntersectionInfo<T> &comps) const {
            auto color = drawing::Color<T>(0, 0, 0);
            const auto material = comps.shape_->material();
            const auto& phong_material = static_cast<shading::PhongMaterial<T>&>(*material);
            const auto phong_shading = shading::PhongShading<T>();

            for (size_t light_i = 0; light_i < scene_.light_count(); ++light_i) {

                const auto& light = scene_.light_at(light_i);

                const auto context = shading::ShadingContext<T>(
                    phong_material,
                    light,
                    comps.point_,
                    comps.eye_,
                    comps.normal_
                );

                color += phong_shading.shade(context);
            }

            return color;
        }

    private:
        const scene::Scene<T>& scene_;
    };
}

#endif //RENDERER_HPP
