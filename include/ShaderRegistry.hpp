#ifndef RAYTRACER_SHADERREGISTRY_HPP
#define RAYTRACER_SHADERREGISTRY_HPP


#include <map>
#include "Shading.hpp"

namespace raytracer::core {
    template<std::floating_point T>
    std::shared_ptr<shading::Shading<T>> create_shader(const shading::ShadingModel model) {
        switch (model) {
            case shading::ShadingModel::Phong:
                return std::make_shared<shading::PhongShading<T> >();
            default:
                return nullptr;
        }
    }

    template<std::floating_point T>
    class ShaderRegistry {
    public:
        ShaderRegistry() = default;
        ~ShaderRegistry() = default;

        ShaderRegistry(const ShaderRegistry &) = delete;
        ShaderRegistry &operator=(const ShaderRegistry &) = delete;
        ShaderRegistry(ShaderRegistry&&) = delete;
        ShaderRegistry& operator=(ShaderRegistry&&) = delete;

        void register_shader(shading::ShadingModel model) {
            const auto shader = create_shader<T>(model);
            if (auto insertion = shaders_.emplace(model, std::move(shader));
                !insertion.second) {
                const auto msg = "Failed to insert ShadingModel";
                throw std::runtime_error(msg);
            }
        }

        std::shared_ptr<shading::Shading<T>>
        get_shader(shading::ShadingModel model) const {
            auto shader = shaders_.find(model);
            if (shader != shaders_.end()) {
                return shader->second;
            }

            return nullptr;
        }

    private:
        std::map<shading::ShadingModel, std::shared_ptr<shading::Shading<T> > > shaders_;
    };
}


#endif //RAYTRACER_SHADERREGISTRY_HPP
