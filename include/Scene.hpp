#ifndef SCENE_HPP
#define SCENE_HPP

#include <algorithm>
#include "Shape.hpp"

namespace raytracer::scene {
    template<std::floating_point T>
    std::optional<Intersection<T> > hit(const std::vector<Intersection<T> > &intersections) {
        auto visible_object_hit = std::find_if(intersections.begin(), intersections.end(),
                                               [](const Intersection<T> &intersection) {
                                                   return intersection.t_ >= 0;
                                               });

        return visible_object_hit != intersections.end() ? std::optional<Intersection<T>>(*visible_object_hit) : std::nullopt;
    }
}

#endif //SCENE_HPP
