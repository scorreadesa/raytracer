#include <iostream>
#include <boost/program_options.hpp>
#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PPMFileWriter.hpp"

template<std::integral T>
T findClosestMultipleOf(T number, T multiple) {
    return ((number + (multiple - 1)) / multiple) * multiple;
}

int main(int argc, const char *argv[]) {
    size_t width, height;
    std::string filepath;

    boost::program_options::options_description desc("Required options");
    desc.add_options()
            ("help,h", "Help menu")
            ("filepath,f", boost::program_options::value<std::string>(&filepath), "Output file path (with filename)")
            ("width", boost::program_options::value<size_t>(&width)->required(), "Canvas width")
            ("height", boost::program_options::value<size_t>(&height)->required(), "Canvas height");

    boost::program_options::positional_options_description positional;
    positional.add("filepath", 1);

    boost::program_options::variables_map options;
    try {
        boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv)
            .options(desc).positional(positional).run(), options);
        boost::program_options::notify(options);
    } catch (const boost::program_options::error &e) {
        std::cerr << "Argument error: " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    }

    std::vector colors{
        raytracer::drawing::Color(228.0, 3.0, 3.0) / 255.0,
        raytracer::drawing::Color(255.0, 140.0, 0.0) / 255.0,
        raytracer::drawing::Color(255.0, 237.0, 0.0) / 255.0,
        raytracer::drawing::Color(0.0, 128.0, 38.0) / 255.0,
        raytracer::drawing::Color(0.0, 77.0, 255.0) / 255.0,
        raytracer::drawing::Color(117.0, 7.0, 235.0) / 255.0,
    };

    std::cout << "Creating a canvas of size: " << height << "x" << width << std::endl;

    std::cout << "Checking padding requirements..." << std::endl;
    std::size_t aligned_height_on_multiple_of_6 = findClosestMultipleOf<std::size_t>(height, 6);

    std::cout << "Padded dimensions: " << height << "x" << aligned_height_on_multiple_of_6 << std::endl;
    raytracer::drawing::Canvas<double> canvas(height, width);

    size_t stripe_size = aligned_height_on_multiple_of_6 / 6;
    size_t current_color_index = 0;

    std::cout << "Stripe size: " << stripe_size << std::endl;

    for (size_t i = 0; i < canvas.height(); i++) {
        if (i % stripe_size == 0 && i != 0) {
            current_color_index++;
        }
        for (size_t j = 0; j < canvas.width(); j++) {
            canvas(i, j) = colors.at(current_color_index);
        }
    }

    FileWriter<decltype(canvas)> ppmfw(std::make_unique<PPMFileWriter<decltype(canvas)> >());
    ppmfw.write(canvas, "", filepath);

    return 0;
}
