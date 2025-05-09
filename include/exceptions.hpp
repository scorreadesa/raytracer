//
// Created by antares on 09.05.25.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>


namespace raytracer::exceptions {
    class ColumnOutOfRangeException : public std::out_of_range {
    public:
        explicit ColumnOutOfRangeException(const std::string &message) : std::out_of_range(message) {
        }
    };

    class RowOutOfRangeException : public std::out_of_range {
    public:
        explicit RowOutOfRangeException(const std::string &message) : std::out_of_range(message) {
        }
    };
}

#endif //EXCEPTIONS_H
