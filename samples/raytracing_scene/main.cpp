#include "Camera.hpp"
#include "FileWriter.hpp"
#include "PhongMaterial.hpp"
#include "PPMFileWriter.hpp"
#include "Renderer.hpp"
#include "SceneBuilder.hpp"
#include "Sphere.hpp"
#include "Transform.hpp"


int main(int argc, char *argv[]) {
    const auto floor_transform = raytracer::maths::Transform4x4<double>::scaling(10, 0.01, 10);
    const auto floor_mat = raytracer::shading::PhongMaterial<double>(
        raytracer::drawing::Color<double>(1, 0.9, 0.9),
        0.2,
        0.6,
        0.0,
        200
    );

    const auto sphere_floor = raytracer::scene::Sphere<double>(
        floor_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(floor_mat));

    const auto left_wall_transform = raytracer::maths::Transform4x4<double>::translation(0, 0, 5) *
                                     raytracer::maths::Transform4x4<double>::rotation_y(-std::numbers::pi / 4) *
                                     raytracer::maths::Transform4x4<double>::rotation_x(std::numbers::pi / 2) *
                                     raytracer::maths::Transform4x4<double>::scaling(10, 0.01, 10);
    const auto left_wall = raytracer::scene::Sphere<double>(
        left_wall_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(floor_mat));

    const auto right_wall_transform = raytracer::maths::Transform4x4<double>::translation(0, 0, 5) *
                                      raytracer::maths::Transform4x4<double>::rotation_y(std::numbers::pi / 4) *
                                      raytracer::maths::Transform4x4<double>::rotation_x(std::numbers::pi / 2) *
                                      raytracer::maths::Transform4x4<double>::scaling(10, 0.01, 10);
    const auto right_wall = raytracer::scene::Sphere<double>(
        right_wall_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(floor_mat));

    const auto middle_sphere_mat = raytracer::shading::PhongMaterial<double>(
        raytracer::drawing::Color<double>(0.1, 1, 0.5),
        0.2,
        0.7,
        0.3,
        200
    );
    const auto middle_sphere_transform = raytracer::maths::Transform4x4<double>::translation(-0.5, 1, 0.5);
    const auto middle_sphere = raytracer::scene::Sphere<double>(
        middle_sphere_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(middle_sphere_mat)
    );

    const auto right_sphere_mat = raytracer::shading::PhongMaterial<double>(
        raytracer::drawing::Color<double>(0.5, 1, 0.1),
        0.2,
        0.7,
        0.3,
        200
    );
    const auto right_sphere_transform = raytracer::maths::Transform4x4<double>::translation(1.5, 0.5, -0.5) *
                                        raytracer::maths::Transform4x4<double>::scaling(0.5, 0.5, 0.5);
    const auto right_sphere = raytracer::scene::Sphere<double>(
        right_sphere_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(right_sphere_mat)
    );

    const auto left_sphere_transform = raytracer::maths::Transform4x4<double>::translation(-1.5, 0.33, -0.75)
                                       * raytracer::maths::Transform4x4<double>::scaling(0.33, 0.33, 0.33);
    const auto left_sphere_mat = raytracer::shading::PhongMaterial<double>(
        raytracer::drawing::Color<double>(1, 0.8, 0.1),
        0.2,
        0.7,
        0.3,
        200
    );
    const auto left_sphere = raytracer::scene::Sphere<double>(
        left_sphere_transform,
        std::make_shared<raytracer::shading::PhongMaterial<double> >(left_sphere_mat)
    );


    const auto light_source = raytracer::shading::PointLight<double>(
        raytracer::maths::Point3D<double>(-10, 10, -10),
        raytracer::drawing::Color<double>(1, 1, 1)
    );

    const auto world = raytracer::scene::SceneBuilder<double>()
            .with_light(light_source)
            .with_object(sphere_floor)
            .with_object(right_wall)
            .with_object(left_wall)
            .with_object(right_sphere)
            .with_object(middle_sphere)
            .with_object(left_sphere)
            .build();

    const auto camera = raytracer::scene::Camera<double>(
        500, 250, std::numbers::pi / 3,
        raytracer::maths::Point3D<double>(0, 1.5, -5),
        raytracer::maths::Point3D<double>(0, 1, 0),
        raytracer::maths::Vector3D<double>(0, 1, 0));

    const auto renderer = raytracer::core::Renderer<double>(world);
    const auto image = renderer.render(camera);

    FileWriter<raytracer::drawing::Canvas<double> > file_writer(
        std::make_unique<PPMFileWriter<raytracer::drawing::Canvas<double> > >());
    file_writer.write(image, "", "scene.ppm");

    return 0;
}
