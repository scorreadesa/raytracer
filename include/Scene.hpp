#ifndef SCENE_HPP
#define SCENE_HPP

#include <ranges>
#include <algorithm>
#include <list>

#include "Shape.hpp"
#include "PointLight.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    std::optional<Intersection<T> > hit(const std::vector<Intersection<T> > &intersections) {
        auto hits_in_front_of_rays = intersections | std::views::filter([](const Intersection<T> &intersection) {
            return intersection.t_ >= 0;
        });

        auto it = std::ranges::min_element(hits_in_front_of_rays,
                                           [](const Intersection<T> &lhs, const Intersection<T> &rhs) {
                                               return lhs < rhs;
                                           });

        if (it != hits_in_front_of_rays.end())
            return *it;
        return std::nullopt;
    }

    template<std::floating_point T>
    struct IntersectionInfo {
        const Shape<T> *shape_;
        maths::Point3D<T> point_;
        maths::Vector3D<T> eye_;
        maths::Vector3D<T> normal_;
        bool inside_;

        IntersectionInfo() = delete;

        IntersectionInfo(
            const Shape<T> *shape,
            const maths::Point3D<T> &point,
            const maths::Vector3D<T> &eye,
            const maths::Vector3D<T> &normal,
            bool inside
        ) : shape_(shape), point_(point), eye_(eye), normal_(normal), inside_(inside) {
        }
    };

    template<std::floating_point T>
    class Scene {
    public:
        Scene() = default;

        void add_light(const shading::Light<T> &light) {
            light_sources_.emplace_back(light.clone());
        }

        void add_object(const Shape<T> &object) {
            objects_.emplace_back(object.clone());
        }

        [[nodiscard]] size_t object_count() const { return objects_.size(); }
        [[nodiscard]] size_t light_count() const { return light_sources_.size(); }

        [[nodiscard]] bool has_objects() const { return !objects_.empty(); }
        [[nodiscard]] bool has_lights() const { return !light_sources_.empty(); }

        const Shape<T> &object_at(size_t index) { return objects_.at(index); }
        const shading::Light<T> &light_at(size_t index) { return light_sources_.at(index); }

        std::vector<Intersection<T> > intersect(const maths::Ray<T> &ray) const {
            std::vector<Intersection<T> > intersections;

            for (auto &obj: objects_) {
                auto xs = obj->intersect(ray); // xs should return vector<Intersection<T>>
                intersections.insert(intersections.end(), xs.begin(), xs.end());
            }

            std::sort(intersections.begin(), intersections.end());
            return intersections;
        }

    private:
        std::vector<std::unique_ptr<Shape<T> > > objects_;
        std::vector<std::unique_ptr<shading::Light<T> > > light_sources_;
    };

    template<std::floating_point T>
    IntersectionInfo<T> prepare_computations(const Intersection<T> &intersection, const maths::Ray<T> &ray) {
        const auto position = ray.position(intersection.t_);
        auto eye = -ray.direction();
        auto normal = intersection.shape_->normal_at(position);

        const auto dot_normal_eye = dot(normal, eye);
        bool inside = false;
        if (dot_normal_eye < 0) {
            inside = true;
            normal = -normal;
        }

        return IntersectionInfo<T>(intersection.shape_, position, eye, normal, inside);
    }
}

#endif //SCENE_HPP
