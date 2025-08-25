#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Matrix.hpp"
#include "Transform.hpp"

namespace raytracer::scene {

    template<std::floating_point T>
    class Camera {
    public:
        Camera() = default;

        maths::Matrix<T> view_transform(const maths::Point3D<T>& from, const maths::Point3D<T>& to, const maths::Vector3D<T> up) const {

            const auto forward = normalize(to - from);
            const auto normal_up = normalize(up);
            const auto left = cross(forward, normal_up);
            const auto true_up = cross(left, forward);

            const auto orientation = maths::Matrix<T>(4, 4, {
                left.x(), left.y(), left.z(), 0,
                true_up.x(), true_up.y(), true_up.z(), 0,
                -forward.x(), -forward.y(), -forward.z(), 0,
                0, 0, 0, 1
            });

            const auto translation = maths::Transform4x4<T>::translation(-from.x(), -from.y(), -from.z());

            return orientation * translation;
        }
    };
}


#endif //RAYTRACER_CAMERA_HPP