#ifndef SCENE_HPP
#define SCENE_HPP

#include <ranges>

#include "Shape.hpp"

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
}

#endif //SCENE_HPP
