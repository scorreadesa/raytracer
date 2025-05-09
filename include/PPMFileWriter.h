#ifndef PPMFILEWRITER_H
#define PPMFILEWRITER_H

#include "IFileWriter.hpp"
#include <fstream>
#include <sstream>

template <typename Canvas>
class PPMFileWriter final : public IFileWriter<Canvas> {
public:
    void write(const Canvas& canvas, const std::filesystem::path& path, const std::string& filename) const override {

        std::stringstream ss;
        ss << "P3\n" << canvas.width() << " " << canvas.height() << "\n255\n";

        for (std::size_t row = 0; row < canvas.height(); ++row) {
            unsigned current_line_length = 0;
            for (std::size_t col = 0; col < canvas.width(); ++col) {

                auto color = canvas(row, col);

                ss << static_cast<int>(color.red() * 255) << " "
                << static_cast<int>(color.green() * 255) << " "
                << static_cast<int>(color.blue() * 255);

                if (current_line_length == 69) {
                    ss << "\n";
                } else {
                    ss << " ";
                }
                current_line_length += 3;
            }
        }

        std::string image_data = ss.str();
        if (image_data.back() != '\n') {
            image_data.push_back('\n');
        }

        auto filepath = path / filename;
        std::ofstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file " + filepath.string());
        }
        file << image_data;
    }
};

#endif //PPMFILEWRITER_H
