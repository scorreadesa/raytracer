#ifndef SCENEBUILDER_HPP
#define SCENEBUILDER_HPP

#include <vector>
#include "Light.hpp"
#include "Scene.hpp"
#include "Shape.hpp"

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
}

#endif //SCENEBUILDER_HPP
