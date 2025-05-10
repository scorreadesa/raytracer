#ifndef DRAWING_H
#define DRAWING_H

#include <iostream>
#include <vector>
#include "exceptions.hpp"

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

        friend Color<T> operator/(const Color<T> &lhs, T scalar) {
            return Color(lhs.red_ / scalar, lhs.green_ / scalar, lhs.blue_ / scalar);
        }

        friend Color<T> operator/(T scalar, const Color<T> &rhs) {
            return Color(rhs.red_ / scalar, rhs.green_ / scalar, rhs.blue_ / scalar);
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

        Color<T> &operator/=(T scalar) {
            red_ /= scalar;
            green_ /= scalar;
            blue_ /= scalar;
            return *this;
        }
    };

    template<std::floating_point T>
    class Canvas {
    private:
        std::vector<Color<T>> colors_;
        std::size_t height_;
        std::size_t width_;
    public:
        Canvas(std::size_t height, std::size_t width) : height_(height), width_(width), colors_(width * height) {};

        constexpr const Color<T>& operator()(const std::size_t row, const std::size_t col) const noexcept(false) {
            auto err_msg_row = "Row index out of range: "
            + std::to_string(row) + "(valid range 0 <= row < " + std::to_string(height_) + ")";
            if (row >= height_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            auto err_msg_col = "Col index out of range: "
            + std::to_string(col) + "(valid range 0 <= col < " + std::to_string(width_) + ")";
            if (col >= width_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return colors_[row * width_ + col];
        }

        constexpr Color<T>& operator()(const std::size_t row, const std::size_t col) noexcept(false) {
            auto err_msg_row = "Row index out of range: "
            + std::to_string(row) + " (valid range 0 <= row < " + std::to_string(height_) + ")";
            if (row >= height_) {
                throw exceptions::RowOutOfRangeException(err_msg_row);
            }

            auto err_msg_col = "Col index out of range: "
            + std::to_string(col) + " (valid range 0 <= col < " + std::to_string(width_) + ")";
            if (col >= width_) {
                throw exceptions::ColumnOutOfRangeException(err_msg_col);
            }

            return colors_[row * width_ + col];
        }

        [[nodiscard]] constexpr std::size_t height() const noexcept {
            return height_;
        }

        [[nodiscard]] constexpr std::size_t width() const noexcept {
            return width_;
        }
    };
}

#endif //DRAWING_H
