#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "IFileWriter.hpp"

template<typename T>
class FileWriter {
public:
    explicit FileWriter(std::unique_ptr<IFileWriter<T> > writer) : writer_(std::move(writer)) {
    }

    void write(const T &data, const std::filesystem::path &path, const std::string &file) {
        writer_->write(data, path, file);
    }

private:
    std::unique_ptr<IFileWriter<T> > writer_;
};

#endif //FILEWRITER_H
