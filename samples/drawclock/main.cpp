#include <boost/program_options.hpp>
#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PPMFileWriter.hpp"
#include "../../include/maths.hpp"
#include "../../include/Transform.hpp"

int main(int argc, char *argv[]) {
    std::string filepath;
    std::size_t height, width;
    double r, g, b;

    boost::program_options::options_description desc("Required options");
    desc.add_options()
            ("filepath", boost::program_options::value<std::string>(&filepath)->required(),
             "Output filepath (with filename)")
            ("height", boost::program_options::value<std::size_t>(&height)->required(), "Canvas height")
            ("width", boost::program_options::value<std::size_t>(&width)->required(), "Canvas width")
            ("r", boost::program_options::value<double>(&r)->required(), "Red (0.0 - 1.0")
            ("g", boost::program_options::value<double>(&g)->required(), "Green (0.0 - 1.0")
            ("b", boost::program_options::value<double>(&b)->required(), "Blue (0.0 - 1.0");

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

    const double radius = 0.375 * static_cast<double>(width);

    auto canvas = raytracer::drawing::Canvas<double>(height, width);

    const size_t center_y = (height - 1) / 2;
    const size_t center_x = (width - 1) / 2;
    canvas(center_y, center_x) = raytracer::drawing::Color<double>(r, g, b);

    std::vector<raytracer::maths::Point3D<double> > points;
    auto point = raytracer::maths::Point3D<double>(1, 0, 0);
    double angle = 0;
    points.push_back(point);

    for (size_t i = 0; i < 11; i++) {
        angle += 30;
        double angle_rad = raytracer::maths::deg2rad(angle);
        const auto rotation_z = raytracer::maths::Transform4x4<double>::rotation_z(angle_rad);
        auto next_point = rotation_z * point;
        next_point = next_point * radius;
        points.push_back(next_point);
    }

    for (const auto &pt: points) {
        const double x_coord = pt.x() + static_cast<double>(center_x);
        const double y_coord = pt.y() + static_cast<double>(center_y);
        canvas(static_cast<size_t>(y_coord), static_cast<size_t>(x_coord)) = raytracer::drawing::Color<double>(r, g, b);
    }


    FileWriter<decltype(canvas)> ppmfw(std::make_unique<PPMFileWriter<decltype(canvas)> >());
    ppmfw.write(canvas, "", filepath);

    return 0;
}
