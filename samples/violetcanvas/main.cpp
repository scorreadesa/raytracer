#include "../../include/drawing.hpp"
#include "../../include/FileWriter.hpp"
#include "../../include/PPMFileWriter.hpp"

int main(int argc, const char *argv[]) {

    double r = 127;
    double g = 0;
    double b = 255;

    raytracer::drawing::Canvas<double> canvas(500, 750);
    for (size_t row = 0; row < canvas.height(); ++row) {
        for (size_t col = 0; col < canvas.width(); ++col) {
            canvas(row, col) = raytracer::drawing::Color<double>(r, g, b);
        }
    }

    FileWriter<decltype(canvas)>
    ppmfw(std::make_unique<PPMFileWriter<decltype(canvas)>>());
    ppmfw.write(canvas, "", "violet.ppm");

    return 0;
}
