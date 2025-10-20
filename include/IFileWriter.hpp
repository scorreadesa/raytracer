#ifndef IFILEWRITER_H
#define IFILEWRITER_H
#include <filesystem>

template<typename T>
class IFileWriter {
public:
    IFileWriter() = default;

    virtual ~IFileWriter() = default;

    IFileWriter(const IFileWriter&) = delete;
    IFileWriter& operator=(const IFileWriter&) = delete;
    IFileWriter(IFileWriter&&) = delete;
    IFileWriter& operator=(IFileWriter&&) = delete;

    virtual void write(const T &data, const std::filesystem::path &path, const std::string &filename) const = 0;
};

#endif //IFILEWRITER_H
