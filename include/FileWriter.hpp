#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "IFileWriter.hpp"

template<typename Canvas>
class FileWriter {
public:
    explicit FileWriter(std::unique_ptr<IFileWriter<Canvas> > writer) : writer_(std::move(writer)) {
    }

    void write(const Canvas& canvas, const std::filesystem::path& path, const std::string& file) {
        writer_->write(canvas, path, file);
    }

private:
    std::unique_ptr<IFileWriter<Canvas> > writer_;
};

#endif //FILEWRITER_H
