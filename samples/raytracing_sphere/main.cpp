#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PhongShading.hpp"
#include "../../include/Point3D.hpp"
#include "../../include/Vector3D.hpp"
#include "../../include/PPMFileWriter.hpp"
#include "../../include/Scene.hpp"
#include "../../include/Sphere.hpp"
#include <boost/program_options.hpp>

#include <yaml-cpp/yaml.h>

#include "../../include/Transform.hpp"

int main(int argc, char *argv[]) {
    std::string config_file;

    boost::program_options::options_description desc("Required options");
    desc.add_options()
            ("help", "Help menu")
            ("config", boost::program_options::value<std::string>(&config_file)->required(), "General config file");
    boost::program_options::positional_options_description positional;
    positional.add("config", 1);

    boost::program_options::variables_map options;

    try {

        boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv)
            .options(desc).positional(positional).run(), options
        );
        boost::program_options::notify(options);

    } catch (const boost::program_options::error &e) {
        std::cerr << "Argument error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }

    YAML::Node config = YAML::LoadFile(config_file);

    // Get output file
    const auto output_file = config["output"].as<std::string>();

    // Initialize canvas
    const auto canvas_width = config["canvas"]["resolution"]["width"].as<size_t>();
    const auto canvas_height = config["canvas"]["resolution"]["height"].as<size_t>();

    auto canvas = raytracer::drawing::Canvas<double>(canvas_height, canvas_width);

    // Initialize lighting
    auto light_pos_x = config["scene"]["lighting"]["position"][0].as<double>();
    auto light_pos_y = config["scene"]["lighting"]["position"][1].as<double>();
    auto light_pos_z = config["scene"]["lighting"]["position"][2].as<double>();
    auto light_r = config["scene"]["lighting"]["intensity"][0].as<double>();
    auto light_g = config["scene"]["lighting"]["intensity"][1].as<double>();
    auto light_b = config["scene"]["lighting"]["intensity"][2].as<double>();

    raytracer::shading::PointLight<double> point_light(
        raytracer::maths::Point3D<double>(light_pos_x, light_pos_y, light_pos_z),
        raytracer::drawing::Color<double>(light_r, light_g, light_b)
    );
    std::clog << "Point Light:\n"
    << "\tPosition: " << point_light.position_ << "\n"
    << "\tIntensity: " << point_light.intensity_ << std::endl;

    // Object
    auto transform = raytracer::maths::Matrix<double>::identity(4);
    auto objects = config["scene"]["objects"]["sphere"];
    auto material = raytracer::shading::Material<double>();

    for (const auto& object : objects) {

        const auto key = object.first.as<std::string>();

        if (key == "transform") {
            const auto transform_node = objects["transform"];

            if (transform_node["scaling"]) {
                const auto scaling = transform_node["scaling"];
                const auto scaling_x = scaling[0].as<double>();
                const auto scaling_y = scaling[1].as<double>();
                const auto scaling_z = scaling[2].as<double>();
                const auto scaling_matrix = raytracer::maths::Transform4x4<double>::scaling(scaling_x, scaling_y, scaling_z);
                std::clog << "Scaling: " << scaling_matrix << std::endl;
                transform *= scaling_matrix;
            }
            if (transform_node["translation"]) {
                const auto translation = transform_node["translation"];
                const auto translation_x = translation[0].as<double>();
                const auto translation_y = translation[1].as<double>();
                const auto translation_z = translation[2].as<double>();
                const auto translation_matrix = raytracer::maths::Transform4x4<double>::translation(translation_x, translation_y, translation_z);
                std::clog << "Translation: " << translation_matrix << std::endl;
                transform *= translation_matrix;
            }
            if (transform_node["shearing"]) {
                const auto shearing = transform_node["shearing"];
                const auto xy = shearing[0].as<double>();
                const auto xz = shearing[1].as<double>();
                const auto yx = shearing[2].as<double>();
                const auto yz = shearing[3].as<double>();
                const auto zx = shearing[4].as<double>();
                const auto zy = shearing[5].as<double>();
                const auto shearing_matrix = raytracer::maths::Transform4x4<double>::shearing(xy, xz, yx, yz, zx, zy);
                std::clog << "Shearing: " << shearing_matrix << std::endl;
                transform *= shearing_matrix;
            }
        }
        if (key == "material") {
            const auto r = objects["material"]["color"][0].as<double>();
            const auto g = objects["material"]["color"][1].as<double>();
            const auto b = objects["material"]["color"][2].as<double>();
            const auto color = raytracer::drawing::Color<double>(r, g, b);
            const auto ambient = objects["material"]["ambient"].as<double>();
            const auto diffuse = objects["material"]["diffuse"].as<double>();
            const auto specular = objects["material"]["specular"].as<double>();
            const auto shininess = objects["material"]["shininess"].as<double>();
            material = raytracer::shading::Material<double>(color, ambient, diffuse, specular, shininess);
            std::clog << "Material:\n"
            << "\tColor: " << color << "\n"
            << "\tAmbient: " << ambient << "\n"
            << "\tDiffuse: " << diffuse << "\n"
            << "\tSpecular: " << specular << "\n"
            << "\tShininess: " << shininess << std::endl;
        }
    }

    std::clog << "Transform: " << transform << std::endl;

    const auto sphere = raytracer::scene::Sphere<double>(transform, material);

    const raytracer::maths::Point3D<double> ray_origin(0, 0, -5);
    constexpr size_t wall_size = 7;
    double pixel_size = static_cast<double>(wall_size) / static_cast<double>(canvas_height);
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
    file_writer.write(canvas, "", output_file);

    return 0;
}
