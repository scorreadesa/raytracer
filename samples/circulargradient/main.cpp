#include <iostream>
#include <boost/program_options.hpp>
#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/maths.hpp"
#include "../../include/PPMFileWriter.hpp"

using raytracer::drawing::Canvas;
using raytracer::drawing::Color;
using raytracer::maths::lerp;

template<std::floating_point T>
void fillCircularGradient(Canvas<T> &canvas, Color<T> &center_color, Color<T> &edge_color) {
    const T center_row = static_cast<T>(canvas.height() - 1) / 2.0;
    const T center_col = static_cast<T>(canvas.width() - 1) / 2.0;
    const T max_dist = std::sqrt(std::pow(center_col, 2) + std::pow(center_row, 2));

    for (std::size_t row = 0; row < canvas.height(); ++row) {
        for (std::size_t col = 0; col < canvas.width(); ++col) {
            T dy = static_cast<T>(row) - center_row;
            T dx = static_cast<T>(col) - center_col;
            T dist = std::sqrt(dx * dx + dy * dy);
            T t = dist / max_dist;

            T r = lerp(center_color.red(), edge_color.red(), t);
            T g = lerp(center_color.green(), edge_color.green(), t);
            T b = lerp(center_color.blue(), edge_color.blue(), t);

            canvas(row, col) = Color<T>(r, g, b);
        }
    }
}

int main(int argc, const char *argv[])
{
    size_t width = 750, height = 500;
    std::string filename;
    double start_r = 0.0, start_g = 0.0, start_b = 0.0;
    double end_r = 0.0, end_g = 0.0, end_b = 0.0;

    boost::program_options::options_description desc("Required options");
    desc.add_options()
            ("help", "Help menu")
            ("filepath,f", boost::program_options::value<std::string>(&filename)->required(), "Output file path (with filename")
            ("width,w", boost::program_options::value<size_t>(&width)->required(), "Canvas width")
            ("height,h", boost::program_options::value<size_t>(&height)->required(), "Canvas height")
            ("start_r", boost::program_options::value<double>(&start_r), "Start r")
            ("start_g", boost::program_options::value<double>(&start_g), "Start g")
            ("start_b", boost::program_options::value<double>(&start_b), "Start b")
            ("end_r", boost::program_options::value<double>(&end_r), "End r")
            ("end_g", boost::program_options::value<double>(&end_g), "End g")
            ("end_b", boost::program_options::value<double>(&end_b), "End b");

    boost::program_options::positional_options_description positional;
    positional.add("filepath", 1);

    boost::program_options::variables_map options;
    try {

        boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv)
            .options(desc).positional(positional).run(), options);
        boost::program_options::notify(options);

    } catch (const boost::program_options::error& e) {
        std::cerr << "Argument error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }


    Canvas<double> canvas(height, width);
    Color start_color(start_r, start_g, start_b);
    Color end_color(end_r, end_g, end_b);
    fillCircularGradient(canvas, start_color, end_color);

    FileWriter<decltype(canvas)> ppmfw(std::make_unique<PPMFileWriter<decltype(canvas)> >());
    ppmfw.write(canvas, "", filename);

    return 0;
}
