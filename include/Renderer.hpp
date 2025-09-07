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

        drawing::Color<T> color_at(const maths::Ray<T>& ray) const {

            auto intersections = scene_.intersect(ray);
            auto hit = scene::hit(intersections);
            if (!hit) {
                return drawing::Color<T>(0, 0, 0);
            }

            auto comps = scene::prepare_computations(hit.value(), ray);
            return shade_hit(comps);
        }

        drawing::Canvas<T> render(const scene::Camera<T>& camera) const {
            auto canvas = drawing::Canvas<T>(camera.vsize(), camera.hsize());
            for (size_t y = 0; y < camera.vsize(); y++) {
                for (size_t x = 0; x < camera.hsize(); x++) {
                    const auto ray = camera.ray_for_pixel(x, y);
                    const auto color = color_at(ray);
                    canvas(y, x) = clamp(color);
                }
            }
            return canvas;
        }

    private:
        const scene::Scene<T>& scene_;
    };
}

#endif //RENDERER_HPP
