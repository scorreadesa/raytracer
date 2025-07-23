#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PhongShading.hpp"
#include "../../include/Point3D.hpp"
#include "../../include/Vector3D.hpp"
#include "../../include/PPMFileWriter.hpp"
#include "../../include/Scene.hpp"
#include "../../include/Sphere.hpp"

int main(int argc, char *argv[]) {

    constexpr size_t canvas_height = 400;
    constexpr size_t canvas_width = 400;

    auto canvas = raytracer::drawing::Canvas<double>(canvas_height, canvas_width);

    const auto material = raytracer::shading::Material<double>(
        raytracer::drawing::Color<double>(1, 0.2, 1),
        0.1,
        0.9,
        0.9,
        200.0
    );

    const auto point_light = raytracer::shading::PointLight<double>(
        raytracer::maths::Point3D<double>(-10, 10, -10),
        raytracer::drawing::Color<double>(1, 1, 1)
    );

    const auto sphere = raytracer::scene::Sphere<double>(material);

    const raytracer::maths::Point3D<double> ray_origin(0, 0, -5);
    constexpr size_t wall_size = 7;
    constexpr double pixel_size = static_cast<double>(wall_size) / static_cast<double>(canvas_height);
    constexpr double half = static_cast<double>(wall_size) / 2.0;

    const auto phong = raytracer::shading::PhongShading<double>();

    for (size_t y = 0; y < canvas_height; y++) {

        const double world_y = half - pixel_size * (static_cast<double>(y) + 0.5);

        for (size_t x = 0; x < canvas_width; x++) {

            constexpr size_t wall_z = 10;

            const double world_x = -half + pixel_size * (static_cast<double>(x) + 0.5);

            auto world_point = raytracer::maths::Point3D(world_x, world_y, static_cast<double>(wall_z));
            auto ray_direction = world_point - ray_origin;
            auto ray = raytracer::maths::Ray(ray_origin, normalize(ray_direction));

            const auto intersections = sphere.intersect(ray);

            if (const auto hit = raytracer::scene::hit(intersections)) {

                const auto point = ray.position(hit.value().t_);
                const auto normal = sphere.normal_at(point);
                const auto eye = -ray.direction();
                const auto color = phong.shade(hit.value().shape_.material(), point_light, point, eye, normal);
                canvas(x, y) = clamp(color);

            }
        }
    }

    FileWriter<raytracer::drawing::Canvas<double> > file_writer(
        std::make_unique<PPMFileWriter<raytracer::drawing::Canvas<double> > >());
    file_writer.write(canvas, "", "sphere.ppm");

    return 0;
}
