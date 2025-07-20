#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/Point3D.hpp"
#include "../../include/Vector3D.hpp"
#include "../../include/PPMFileWriter.hpp"
#include "../../include/Scene.hpp"
#include "../../include/Sphere.hpp"

int main(int argc, char *argv[]) {
    constexpr size_t canvas_height = 200;
    constexpr size_t canvas_width = 200;
    auto canvas = raytracer::drawing::Canvas<double>(canvas_height, canvas_width);
    const auto red = raytracer::drawing::Color(0.6, 0.3, 0.8);
    const auto sphere = raytracer::scene::Sphere<double>();

    const raytracer::maths::Point3D<double> ray_origin(0, 0, -5);
    constexpr size_t wall_size = 7;
    constexpr double pixel_size = static_cast<double>(wall_size) / static_cast<double>(canvas_height);
    constexpr double half = static_cast<double>(wall_size) / 2.0;


    for (size_t y = 0; y < canvas_height; y++) {
        const double world_y = half - pixel_size * (static_cast<double>(y) + 0.5);

        for (size_t x = 0; x < canvas_width; x++) {
            constexpr size_t wall_z = 10;

            const double world_x = -half + pixel_size * (static_cast<double>(x) + 0.5);

            auto world_point = raytracer::maths::Point3D(world_x, world_y, static_cast<double>(wall_z));
            auto ray_direction = world_point - ray_origin;
            auto ray = raytracer::maths::Ray(ray_origin, normalize(ray_direction));

            if (auto intersections = sphere.intersect(ray); raytracer::scene::hit(intersections)) {
                canvas(x, y) = red;
            }
        }
    }

    FileWriter<raytracer::drawing::Canvas<double> > file_writer(
        std::make_unique<PPMFileWriter<raytracer::drawing::Canvas<double> > >());
    file_writer.write(canvas, "", "sphere.ppm");

    return 0;
}
