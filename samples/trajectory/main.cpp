#include <iostream>
#include <boost/program_options.hpp>
#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PPMFileWriter.hpp"
#include "../../include/Point3D.hpp"
#include "../../include/Vector3D.hpp"

struct Projectile {
    raytracer::maths::Point3D<double> position_;
    raytracer::maths::Vector3D<double> velocity_;

    Projectile(const raytracer::maths::Point3D<double> &position,
               const raytracer::maths::Vector3D<double> &velocity) : position_(position),
                                                                     velocity_(velocity) {
    }
};

struct Environment {
    raytracer::maths::Vector3D<double> gravity_;
    raytracer::maths::Vector3D<double> wind_;

    Environment(const raytracer::maths::Vector3D<double> &gravity,
                const raytracer::maths::Vector3D<double> &wind) : gravity_(gravity),
                                                                  wind_(wind) {
    }
};

void tick(Environment &env, Projectile &projectile) {
    projectile.position_ = projectile.position_ + projectile.velocity_;
    projectile.velocity_ = projectile.velocity_ + env.gravity_ + env.wind_;
}

int main(int argc, char **argv) {
    std::string filepath;
    std::size_t width, height;
    double r, g, b;

    boost::program_options::options_description desc("Required options");
    desc.add_options()
            ("filepath", boost::program_options::value<std::string>(&filepath)->required(),
             "Output file path (with filename)")
            ("width", boost::program_options::value<std::size_t>(&width)->required(), "Canvas width")
            ("height", boost::program_options::value<std::size_t>(&height)->required(), "Canvas height")
            ("r", boost::program_options::value<double>(&r)->required(), "Red (0.0 - 1.0)")
            ("g", boost::program_options::value<double>(&g)->required(), "Green (0.0 - 1.0)")
            ("b", boost::program_options::value<double>(&b)->required(), "Blue (0.0 - 1.0)");

    boost::program_options::positional_options_description pos;
    pos.add("filepath", 1);

    boost::program_options::variables_map vm;
    try {
        boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
                                      .options(desc).positional(pos).run(), vm);

        boost::program_options::notify(vm);
    } catch (const boost::program_options::error &e) {
        std::cerr << "Argument error: " << e.what() << "\n";
        std::cerr << desc << '\n';
        return 1;
    }

    auto projectile = Projectile(raytracer::maths::Point3D<double>(0.0, 1.0, 0.0),
                                 normalize(raytracer::maths::Vector3D<double>(1.0, 1.8, 0.0)) * 11.25);

    auto environment = Environment(raytracer::maths::Vector3D<double>(0.0, -0.1, 0.0),
                                   raytracer::maths::Vector3D<double>(-0.01, 0.0, 0.0));

    raytracer::drawing::Canvas<double> canvas(height, width);

    unsigned steps = 0;
    while (projectile.position_.y() > 0.0) {
        canvas(static_cast<std::size_t>(static_cast<double>(canvas.height()) - projectile.position_.y()),
               static_cast<std::size_t>(projectile.position_.x())) = raytracer::drawing::Color<double>(r, g, b);
        steps++;
        tick(environment, projectile);
    }

    FileWriter<decltype(canvas)> ppmfw(std::make_unique<PPMFileWriter<decltype(canvas)> >());
    ppmfw.write(canvas, "", filepath);

    return 0;
}
