#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "CofactorExpansion.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Transform.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    class Camera {
    public:
        Camera(const size_t h_size, const size_t v_size, const T fov,
               const maths::Point3D<T> from, const maths::Point3D<T> &to, const maths::Vector3D<T> &up,
               const maths::Solver<T> &solver = maths::CofactorExpansion<T>())
            : h_size_(h_size), v_size_(v_size), fov_(fov), transform_(view_transform(from, to, up)),
              aspect_(static_cast<T>(h_size) / static_cast<T>(v_size)),
              half_view_(std::tan(fov / 2)),
              half_width_(aspect_ >= static_cast<T>(1) ? half_view_ : half_view_ * static_cast<T>(aspect_)),
              half_height_(aspect_ >= static_cast<T>(1) ? half_view_ / static_cast<T>(aspect_) : half_view_),
              pixel_size_(half_width_ * static_cast<T>(2) / static_cast<T>(h_size)), solver_(solver.clone()) {
        }

        Camera(const size_t h_size, const size_t v_size, const T fov,
               const maths::Matrix<T> &transform = maths::Matrix<T>::identity(4),
               const maths::Solver<T> &solver = maths::CofactorExpansion<T>())
            : h_size_(h_size), v_size_(v_size), fov_(fov),
              transform_(transform), aspect_(static_cast<T>(h_size) / static_cast<T>(v_size)),
              half_view_(std::tan(fov / 2)),
              half_width_(aspect_ >= static_cast<T>(1) ? half_view_ : half_view_ * static_cast<T>(aspect_)),
              half_height_(aspect_ >= static_cast<T>(1) ? half_view_ / static_cast<T>(aspect_) : half_view_),
              pixel_size_(half_width_ * static_cast<T>(2) / static_cast<T>(h_size)),
              solver_(solver.clone()) {
        }

        maths::Matrix<T> view_transform(const maths::Point3D<T> &from,
                                        const maths::Point3D<T> &to,
                                        const maths::Vector3D<T> up) const {
            const auto forward = normalize(to - from);
            const auto normal_up = normalize(up);
            const auto left = cross(forward, normal_up);
            const auto true_up = cross(left, forward);

            const auto orientation = maths::Matrix<T>(
                4, 4,
                {
                    left.x(), left.y(), left.z(), 0,
                    true_up.x(), true_up.y(), true_up.z(), 0,
                    -forward.x(), -forward.y(), -forward.z(),
                    0, 0, 0, 0, 1
                });

            const auto translation =
                    maths::Transform4x4<T>::translation(-from.x(), -from.y(), -from.z());

            return orientation * translation;
        }

        [[nodiscard]] size_t hsize() const { return h_size_; }
        [[nodiscard]] size_t vsize() const { return v_size_; }
        T fov() const { return fov_; }
        maths::Matrix<T> transform() const { return transform_; }
        T pixel_size() const { return pixel_size_; }

        maths::Ray<T> ray_for_pixel(size_t px, size_t py) const {
            T x_offset = (static_cast<T>(px) + static_cast<T>(0.5)) * pixel_size_;
            T y_offset = (static_cast<T>(py) + static_cast<T>(0.5)) * pixel_size_;

            T world_x = half_width_ - x_offset;
            T world_y = half_height_ - y_offset;

            const auto pixel = solver_->inverse(transform_) * maths::Point3D<T>(world_x, world_y, -1);
            const auto origin = solver_->inverse(transform_) * maths::Point3D<T>(0, 0, 0);
            const auto direction = normalize(pixel - origin);

            return maths::Ray<T>(origin, direction);
        }

    private:
        size_t h_size_;
        size_t v_size_;
        T fov_;
        maths::Matrix<T> transform_;
        T aspect_;
        T half_view_;
        T half_width_;
        T half_height_;
        T pixel_size_;
        std::unique_ptr<maths::Solver<T> > solver_;
    };
} // namespace raytracer::scene

#endif // RAYTRACER_CAMERA_HPP
