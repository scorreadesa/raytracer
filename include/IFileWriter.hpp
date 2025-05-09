#ifndef IFILEWRITER_H
#define IFILEWRITER_H
#include <filesystem>

template <typename Canvas>
class IFileWriter {
    public:
    virtual ~IFileWriter() = default;
    virtual void write(const Canvas& canvas, const std::filesystem::path& path, const std::string& filename) const = 0;
};

#endif //IFILEWRITER_H
