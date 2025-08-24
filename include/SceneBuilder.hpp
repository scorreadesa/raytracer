#ifndef SCENEBUILDER_HPP
#define SCENEBUILDER_HPP

#include <vector>
#include "Light.hpp"
#include "Scene.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Transform.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    class SceneBuilder {
    public:
        SceneBuilder() = default;

        ~SceneBuilder() = default;

        SceneBuilder(const SceneBuilder &) = delete;

        SceneBuilder &operator=(const SceneBuilder &) = delete;

        SceneBuilder(SceneBuilder &&) = default;

        SceneBuilder &operator=(SceneBuilder &&) = default;

        SceneBuilder &with_light(const shading::Light<T> &light) {
            light_sources_.emplace_back(light.clone());
            return *this;
        }

        SceneBuilder &with_light(std::unique_ptr<shading::Light<T> > light) {
            light_sources_.emplace_back(std::move(light));
            return *this;
        }

        SceneBuilder &with_object(const Shape<T> &shape) {
            objects_.emplace_back(shape.clone());
            return *this;
        }

        SceneBuilder &with_object(std::unique_ptr<Shape<T> > shape) {
            objects_.emplace_back(std::move(shape));
            return *this;
        }

        Scene<T> build() const {
            Scene<T> scene;
            for (const auto &light: light_sources_) {
                scene.add_light(*light);
            }
            for (const auto &object: objects_) {
                scene.add_object(*object);
            }
            return scene;
        }

    private:
        std::vector<std::unique_ptr<shading::Light<T> > > light_sources_;
        std::vector<std::unique_ptr<Shape<T> > > objects_;
    };

    template<std::floating_point T>
    Scene<T> default_scene() {
        const auto point_light = raytracer::shading::PointLight<T>(
    raytracer::maths::Point3D<T>(-10, 10, -10),
    raytracer::drawing::Color<T>(1, 1, 1)
);

        const auto material = std::make_shared<raytracer::shading::PhongMaterial<T> >(
            raytracer::drawing::Color<T>(0.8, 1.0, 0.6),
            0.1,
            0.7,
            0.2,
            200.0
        );
        const auto s1 = scene::Sphere<T>(material);

        const auto scaling = maths::Transform4x4<T>::scaling(0.5, 0.5, 0.5);
        const auto s2 = raytracer::scene::Sphere<T>(scaling);

        auto scene = raytracer::scene::SceneBuilder<T>()
                .with_light(point_light)
                .with_object(s1)
                .with_object(s2)
                .build();

        return scene;
    }

}

#endif //SCENEBUILDER_HPP
