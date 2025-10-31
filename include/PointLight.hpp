#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP
#include "Light.hpp"

namespace raytracer::shading {
    template<std::floating_point T>
    class PointLight final : public Light<T> {
    private:
        maths::Point3D<T> position_;
        drawing::Color<T> intensity_;

    public:
        PointLight() = default;

        PointLight(const PointLight&) = default;
        PointLight& operator=(const PointLight&) = default;
        PointLight(PointLight&&) = default;
        PointLight& operator=(PointLight&&) = default;

        PointLight(const maths::Point3D<T> &position, const drawing::Color<T> &color)
            : position_(position), intensity_(color) {
        }

        maths::Point3D<T> position() const override {
            return position_;
        }

        drawing::Color<T> intensity() const override {
            return intensity_;
        };

        std::unique_ptr<Light<T> > clone() const override {
            return std::make_unique<PointLight<T> >(*this);
        }
    };
}

#endif //POINTLIGHT_HPP
