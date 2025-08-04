//
// Created by antares on 09.05.25.
//

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>


namespace raytracer::exceptions {
    class ColumnOutOfRangeException final : public std::out_of_range {
    public:
        explicit ColumnOutOfRangeException(const std::string &message) : std::out_of_range(message) {
        }
    };

    class RowOutOfRangeException final : public std::out_of_range {
    public:
        explicit RowOutOfRangeException(const std::string &message) : std::out_of_range(message) {
        }
    };

    class ShapeMismatchException final : public std::out_of_range {
    public:
        explicit ShapeMismatchException(const std::string &message) : std::out_of_range(message) {
        }
    };

    class NotInvertibleMatrixException final : public std::invalid_argument {
    public:
        explicit NotInvertibleMatrixException(const std::string &message) : std::invalid_argument(message) {
        }
    };
}

#endif //EXCEPTIONS_H
