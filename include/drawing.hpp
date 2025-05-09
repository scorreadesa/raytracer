#ifndef DRAWING_H
#define DRAWING_H

#include <array>

#include "exceptions.h"

namespace raytracer::drawing {

    template<std::floating_point T>
    class Color {
    private:
        T red_;
        T green_;
        T blue_;

    public:
        Color() = default;

        Color(T red, T green, T blue) : red_(red), green_(green), blue_(blue) {
        }

        T red() const { return red_; }
        T green() const { return green_; }
        T blue() const { return blue_; }

        T &red() { return red_; }
        T &green() { return green_; }
        T &blue() { return blue_; }

        friend std::ostream &operator<<(std::ostream &os, const Color &color) {
            os << "(" << color.red_ << ", " << color.green_ << ", " << color.blue_ << ")";
            return os;
        }

        friend Color<T> operator+(const Color<T> &lhs, const Color<T> &rhs) {
            return Color(lhs.red_ + rhs.red_, lhs.green_ + rhs.green_, lhs.blue_ + rhs.blue_);
        }

        friend Color<T> operator-(const Color<T> &lhs, const Color<T> &rhs) {
            return Color(lhs.red_ - rhs.red_, lhs.green_ - rhs.green_, lhs.blue_ - rhs.blue_);
        }

        friend Color<T> operator*(const Color<T> &lhs, T scalar) {
            return Color(lhs.red_ * scalar, lhs.green_ * scalar, lhs.blue_ * scalar);
        }

        friend Color<T> operator*(T scalar, const Color<T> &rhs) {
            return Color(rhs.red_ * scalar, rhs.green_ * scalar, rhs.blue_ * scalar);
        }

        friend Color<T> operator*(const Color<T> &lhs, const Color<T> &rhs) {
            return Color(lhs.red_ * rhs.red_, lhs.green_ * rhs.green_, lhs.blue_ * rhs.blue_);
        }

        Color<T> &operator+=(const Color<T> &rhs) {
            red_ += rhs.red_;
            green_ += rhs.green_;
            blue_ += rhs.blue_;
            return *this;
        }

        Color<T> &operator-=(const Color<T> &rhs) {
            red_ -= rhs.red_;
            green_ -= rhs.green_;
            blue_ -= rhs.blue_;
            return *this;
        }

        Color<T> &operator*=(const Color<T> &rhs) {
            red_ *= rhs.red_;
            green_ *= rhs.green_;
            blue_ *= rhs.blue_;
            return *this;
        }

        Color<T> &operator*=(T scalar) {
            red_ *= scalar;
            green_ *= scalar;
            blue_ *= scalar;
            return *this;
        }
    };

    template<std::floating_point T, std::size_t Height, std::size_t Width>
    class Canvas {
    private:
        std::array<Color<T>, Height * Width> colors_;
    public:
        Canvas() = default;

        constexpr const Color<T>& operator()(const std::size_t row, const std::size_t col) const noexcept(false) {
            auto err_msg_row = "Row index out of range: "
            + std::to_string(row) + "(valid range 0 <= row <=" + std::to_string(row) + ")";
            if (row >= Height) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            auto err_msg_col = "Col index out of range: "
            + std::to_string(col) + "(valid range 0 <= col " + std::to_string(col) + ")";
            if (col >= Width) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return colors_[row * Width + col];
        }

        constexpr Color<T>& operator()(const std::size_t row, const std::size_t col) noexcept(false) {
            auto err_msg_row = "Row index out of range: "
            + std::to_string(row) + " (valid range 0 <= row < " + std::to_string(row) + ")";
            if (row >= Height) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            auto err_msg_col = "Col index out of range: "
            + std::to_string(col) + " (valid range 0 <= col < " + std::to_string(col) + ")";
            if (col >= Width) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return colors_[row * Width + col];
        }

        [[nodiscard]] constexpr std::size_t height() const noexcept {
            return Height;
        }

        [[nodiscard]] constexpr std::size_t width() const noexcept {
            return Width;
        }
    };
}

#endif //DRAWING_H
