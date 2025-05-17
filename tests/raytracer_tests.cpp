#include <gtest/gtest.h>
#include <boost/math/special_functions/next.hpp>

#include "../include/drawing.hpp"
#include "../include/maths.hpp"

TEST(FPTests, ApproximatelyEqualEpsilonAddSmall) {
    float a = 0.0;
    float b = 0.0;

    for (unsigned int i = 0; i < 10000; i++) {
        a += 0.001;
        b += 0.001;
        bool almostEqualEpsilon = raytracer::maths::almost_equal_epsilon(a, b);
        EXPECT_TRUE(almostEqualEpsilon);
    }
}

TEST(FPTests, ApproximatelyEqualEpsilonMultiplySmall) {
    float a = 0.01;
    float b = 0.01;

    for (unsigned int i = 0; i < 10000; i++) {
        a *= 0.001;
        b *= 0.001;
        bool almostEqualEpsilon = raytracer::maths::almost_equal_epsilon(a, b);
        EXPECT_TRUE(almostEqualEpsilon);
    }
}

TEST(PointTests, CreatePoint) {
    raytracer::maths::Point3D point(0.0, 0.0, 0.0);
    EXPECT_NEAR(point.x(), 0.0, 1e-6);
    EXPECT_NEAR(point.y(), 0.0, 1e-6);
    EXPECT_NEAR(point.z(), 0.0, 1e-6);
    EXPECT_NEAR(point.w(), 1.0, 1e-6);
}

TEST(PointTests, MovePointWithRightVectorAdd) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    raytracer::maths::Point3D p(1.0, 2.0, 3.0);

    auto new_p = p + v;

    EXPECT_NEAR(new_p.x(), 2.0, 1e-6);
    EXPECT_NEAR(new_p.y(), 4.0, 1e-6);
    EXPECT_NEAR(new_p.z(), 6.0, 1e-6);
    EXPECT_NEAR(new_p.w(), 1.0, 1e-6);
}

TEST(PointTests, MovePointWithLeftVectorAdd) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    raytracer::maths::Point3D p(1.0, 2.0, 3.0);

    auto new_p = v + p;

    EXPECT_NEAR(new_p.x(), 2.0, 1e-6);
    EXPECT_NEAR(new_p.y(), 4.0, 1e-6);
    EXPECT_NEAR(new_p.z(), 6.0, 1e-6);
    EXPECT_NEAR(new_p.w(), 1.0, 1e-6);
}

TEST(PointTests, MovePointBackward) {
    raytracer::maths::Vector3D v(5.0, 6.0, 7.0);
    raytracer::maths::Point3D p(3.0, 2.0, 1.0);
    auto new_p = p - v;

    EXPECT_NEAR(new_p.x(), -2.0, 1e-6);
    EXPECT_NEAR(new_p.y(), -4.0, 1e-6);
    EXPECT_NEAR(new_p.z(), -6.0, 1e-6);
    EXPECT_NEAR(new_p.w(), 1.0, 1e-6);
}

TEST(PointTests, ChangePoint) {
    raytracer::maths::Point3D point(1.0, 2.0, 3.0);
    point.x() = 2.0;
    point.y() = 4.0;
    point.z() = 8.0;
    EXPECT_NEAR(point.x(), 2.0, 1e-6);
    EXPECT_NEAR(point.y(), 4.0, 1e-6);
    EXPECT_NEAR(point.z(), 8.0, 1e-6);
    EXPECT_NEAR(point.w(), 1.0, 1e-6);
}

TEST(VectorTests, CreateVector) {
    raytracer::maths::Vector3D vector(0.0, 0.0, 0.0);
    EXPECT_NEAR(vector.x(), 0.0, 1e-6);
    EXPECT_NEAR(vector.y(), 0.0, 1e-6);
    EXPECT_NEAR(vector.z(), 0.0, 1e-6);
    EXPECT_NEAR(vector.w(), 0.0, 1e-6);
}

TEST(VectorTests, ChangeVector) {
    raytracer::maths::Vector3D vector(1.0, 2.0, 3.0);
    vector.x() = 2.0;
    vector.y() = 4.0;
    vector.z() = 8.0;
    EXPECT_NEAR(vector.x(), 2.0, 1e-6);
    EXPECT_NEAR(vector.y(), 4.0, 1e-6);
    EXPECT_NEAR(vector.z(), 8.0, 1e-6);
    EXPECT_NEAR(vector.w(), 0.0, 1e-6);
}

TEST(VectorTests, AddTwoVectors) {
    raytracer::maths::Vector3D v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D v2(2.0, 4.0, 4.0);
    auto result = v1 + v2;
    EXPECT_NEAR(result.x(), 3.0, 1e-6);
    EXPECT_NEAR(result.y(), 6.0, 1e-6);
    EXPECT_NEAR(result.z(), 7.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, SubTwoVectors) {
    raytracer::maths::Vector3D v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D v2(2.0, 4.0, 4.0);
    auto result = v1 - v2;
    EXPECT_NEAR(result.x(), -1.0, 1e-6);
    EXPECT_NEAR(result.y(), -2.0, 1e-6);
    EXPECT_NEAR(result.z(), -1.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, LeftMultByScalar) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    auto result = 2 * v;
    EXPECT_NEAR(result.x(), 2.0, 1e-6);
    EXPECT_NEAR(result.y(), 4.0, 1e-6);
    EXPECT_NEAR(result.z(), 6.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, RightMultByScalar) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    auto result = v * 2;
    EXPECT_NEAR(result.x(), 2.0, 1e-6);
    EXPECT_NEAR(result.y(), 4.0, 1e-6);
    EXPECT_NEAR(result.z(), 6.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, CompoundAddTwoVectors) {
    raytracer::maths::Vector3D v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D v2(2.0, 4.0, 4.0);
    v1 += v2;
    EXPECT_NEAR(v1.x(), 3.0, 1e-6);
    EXPECT_NEAR(v1.y(), 6.0, 1e-6);
    EXPECT_NEAR(v1.z(), 7.0, 1e-6);
    EXPECT_NEAR(v1.w(), 0.0, 1e-6);
}

TEST(VectorTests, CompoundSubTwoVectors) {
    raytracer::maths::Vector3D v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D v2(2.0, 4.0, 4.0);
    v1 -= v2;
    EXPECT_NEAR(v1.x(), -1.0, 1e-6);
    EXPECT_NEAR(v1.y(), -2.0, 1e-6);
    EXPECT_NEAR(v1.z(), -1.0, 1e-6);
    EXPECT_NEAR(v1.w(), 0.0, 1e-6);
}

TEST(VectorTests, CompoundMultVectorScalar) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    v *= 2;
    EXPECT_NEAR(v.x(), 2.0, 1e-6);
    EXPECT_NEAR(v.y(), 4.0, 1e-6);
    EXPECT_NEAR(v.z(), 6.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, GetVectorFromPointSubtraction) {
    raytracer::maths::Point3D v1(3.0, 2.0, 1.0);
    raytracer::maths::Point3D v2(5.0, 6.0, 7.0);
    auto result = v1 - v2;

    EXPECT_NEAR(result.x(), -2.0, 1e-6);
    EXPECT_NEAR(result.y(), -4.0, 1e-6);
    EXPECT_NEAR(result.z(), -6.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, NegateVector) {
    raytracer::maths::Vector3D v(1.0, -2.0, 1.0);
    -v;
    EXPECT_NEAR(v.x(), -1.0, 1e-6);
    EXPECT_NEAR(v.y(), 2.0, 1e-6);
    EXPECT_NEAR(v.z(), -1.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, RightDivByScalar) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    auto result = v / 2;
    EXPECT_NEAR(result.x(), 0.5, 1e-6);
    EXPECT_NEAR(result.y(), 1.0, 1e-6);
    EXPECT_NEAR(result.z(), 1.5, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat) {
    raytracer::maths::Vector3D<float> v(1.0, 0.0, 0.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble) {
    raytracer::maths::Vector3D v(1.0, 0.0, 0.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat2) {
    raytracer::maths::Vector3D<float> v(0.0, 1.0, 0.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble2) {
    raytracer::maths::Vector3D v(0.0, 1.0, 0.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat3) {
    raytracer::maths::Vector3D<float> v(0.0, 0.0, 1.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble3) {
    raytracer::maths::Vector3D v(0.0, 0.0, 1.0);
    auto length = v.length();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat4) {
    raytracer::maths::Vector3D<float> v(1.0, 2.0, 3.0);
    auto length = v.length();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthDouble4) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    auto length = v.length();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthFloat5) {
    raytracer::maths::Vector3D<float> v(-1.0, -2.0, -3.0);
    auto length = v.length();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthDouble5) {
    raytracer::maths::Vector3D v(-1.0, -2.0, -3.0);
    auto length = v.length();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionFloat) {
    raytracer::maths::Vector3D<float> v(4.0, 0.0, 0.0);
    v.normalize();
    EXPECT_NEAR(v.length(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), 1.0, 1e-6);
    EXPECT_NEAR(v.y(), 0.0, 1e-6);
    EXPECT_NEAR(v.z(), 0.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionDouble) {
    raytracer::maths::Vector3D v(4.0, 0.0, 0.0);
    v.normalize();
    EXPECT_NEAR(v.length(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), 1.0, 1e-6);
    EXPECT_NEAR(v.y(), 0.0, 1e-6);
    EXPECT_NEAR(v.z(), 0.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionFloat2) {
    raytracer::maths::Vector3D<float> v(1.0, 2.0, 3.0);
    v.normalize();
    EXPECT_NEAR(v.length(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionDouble2) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    v.normalize();
    EXPECT_NEAR(v.length(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithFreeFunctionFloat) {
    raytracer::maths::Vector3D<float> v(1.0, 2.0, 3.0);
    auto result = normalize(v);
    EXPECT_NEAR(result.length(), 1.0, 1e-6);
    EXPECT_NEAR(result.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithFreeFunctionDouble2) {
    raytracer::maths::Vector3D<double> v(1.0, 2.0, 3.0);
    auto result = normalize(v);
    EXPECT_NEAR(result.length(), 1.0, 1e-6);
    EXPECT_NEAR(result.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, VectorDotProductFloat) {
    raytracer::maths::Vector3D<float> v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D<float> v2(2.0, 3.0, 4.0);

    float dot_prod = v1.dot(v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);

    dot_prod = dot(v1, v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);
}

TEST(VectorTests, VectorDotProductDouble) {
    raytracer::maths::Vector3D<double> v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D<double> v2(2.0, 3.0, 4.0);

    double dot_prod = v1.dot(v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);

    dot_prod = dot(v1, v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);
}

TEST(VectorTests, VectorCrossProductFloat) {
    raytracer::maths::Vector3D<float> v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D<float> v2(2.0, 3.0, 4.0);

    auto cross_prod_v1v2 = v1.cross(v2);
    EXPECT_NEAR(cross_prod_v1v2.x(), -1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.y(), 2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.z(), -1.0, 1e-6);

    auto cross_prod_v2v1 = v2.cross(v1);
    EXPECT_NEAR(cross_prod_v2v1.x(), 1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.y(), -2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.z(), 1.0, 1e-6);

    cross_prod_v1v2 = cross(v1, v2);
    EXPECT_NEAR(cross_prod_v1v2.x(), -1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.y(), 2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.z(), -1.0, 1e-6);

    cross_prod_v2v1 = cross(v2, v1);
    EXPECT_NEAR(cross_prod_v2v1.x(), 1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.y(), -2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.z(), 1.0, 1e-6);
}

TEST(ColorTests, CreateColor) {
    auto color = raytracer::drawing::Color<double>(1.0, 0.4, 0.6);

    EXPECT_NEAR(color.red(), 1.0, 1e-6);
    EXPECT_NEAR(color.green(), 0.4, 1e-6);
    EXPECT_NEAR(color.blue(), 0.6, 1e-6);

    color.red() = 0.3;
    color.green() = 0.6;
    color.blue() = 0.5;

    EXPECT_NEAR(color.red(), 0.3, 1e-6);
    EXPECT_NEAR(color.green(), 0.6, 1e-6);
    EXPECT_NEAR(color.blue(), 0.5, 1e-6);
}

TEST(ColorTests, AddColors) {
    auto c1 = raytracer::drawing::Color<double>(0.9, 0.6, 0.75);
    auto c2 = raytracer::drawing::Color<double>(0.7, 0.1, 0.25);

    auto result = c1 + c2;

    EXPECT_NEAR(result.red(), 1.6, 1e-6);
    EXPECT_NEAR(result.green(), 0.7, 1e-6);
    EXPECT_NEAR(result.blue(), 1.0, 1e-6);

    c1 += c2;

    EXPECT_NEAR(c1.red(), 1.6, 1e-6);
    EXPECT_NEAR(c1.green(), 0.7, 1e-6);
    EXPECT_NEAR(c1.blue(), 1.0, 1e-6);
}

TEST(ColorTests, SubColors) {
    auto c1 = raytracer::drawing::Color<double>(0.9, 0.6, 0.75);
    auto c2 = raytracer::drawing::Color<double>(0.7, 0.1, 0.25);

    auto result = c1 - c2;

    EXPECT_NEAR(result.red(), 0.2, 1e-6);
    EXPECT_NEAR(result.green(), 0.5, 1e-6);
    EXPECT_NEAR(result.blue(), 0.5, 1e-6);

    c1 -= c2;

    EXPECT_NEAR(c1.red(), 0.2, 1e-6);
    EXPECT_NEAR(c1.green(), 0.5, 1e-6);
    EXPECT_NEAR(c1.blue(), 0.5, 1e-6);
}

TEST(ColorTests, RightMultColorByScalar) {
    auto c1 = raytracer::drawing::Color<double>(0.2, 0.3, 0.4);

    auto result1 = c1 * 2.0;
    EXPECT_NEAR(result1.red(), 0.4, 1e-6);
    EXPECT_NEAR(result1.green(), 0.6, 1e-6);
    EXPECT_NEAR(result1.blue(), 0.8, 1e-6);

    c1 *= 2.0;

    EXPECT_NEAR(c1.red(), 0.4, 1e-6);
    EXPECT_NEAR(c1.green(), 0.6, 1e-6);
    EXPECT_NEAR(c1.blue(), 0.8, 1e-6);
}

TEST(ColorTests, LeftMultColorByScalar) {
    auto c1 = raytracer::drawing::Color<double>(0.2, 0.3, 0.4);

    auto result1 = 2.0 * c1;
    EXPECT_NEAR(result1.red(), 0.4, 1e-6);
    EXPECT_NEAR(result1.green(), 0.6, 1e-6);
    EXPECT_NEAR(result1.blue(), 0.8, 1e-6);

    c1 *= 2.0;

    EXPECT_NEAR(c1.red(), 0.4, 1e-6);
    EXPECT_NEAR(c1.green(), 0.6, 1e-6);
    EXPECT_NEAR(c1.blue(), 0.8, 1e-6);
}

TEST(ColorTests, MultColors) {
    auto c1 = raytracer::drawing::Color<double>(1.0, 0.2, 0.4);
    auto c2 = raytracer::drawing::Color<double>(0.9, 1.0, 0.1);

    auto result = c1 * c2;

    EXPECT_NEAR(result.red(), 0.9, 1e-6);
    EXPECT_NEAR(result.green(), 0.2, 1e-6);
    EXPECT_NEAR(result.blue(), 0.04, 1e-6);

    c1 *= c2;

    EXPECT_NEAR(c1.red(), 0.9, 1e-6);
    EXPECT_NEAR(c1.green(), 0.2, 1e-6);
    EXPECT_NEAR(c1.blue(), 0.04, 1e-6);
}

TEST(CanvasTests, CreateBlackCanvas) {
    raytracer::drawing::Canvas<double> canvas(4, 3);

    for (size_t row = 0; row < canvas.height(); ++row) {

        for (size_t col = 0; col < canvas.width(); ++col) {

            auto color = canvas(row, col);
            EXPECT_NEAR(color.red(), 0.0, 1e-6);
            EXPECT_NEAR(color.green(), 0.0, 1e-6);
            EXPECT_NEAR(color.blue(), 0.0, 1e-6);
        }
    }
}

TEST(CanvasTests, MakeRedCanvas) {
    raytracer::drawing::Canvas<double> canvas(4, 3);

    for (size_t row = 0; row < canvas.height(); ++row) {

        for (size_t col = 0; col < canvas.width(); ++col) {

            canvas(row, col) = raytracer::drawing::Color(1.0, 0.0, 0.0);
        }
    }

    for (size_t row = 0; row < canvas.height(); ++row) {

        for (size_t col = 0; col < canvas.width(); ++col) {

            EXPECT_NEAR(canvas(row, col).red(), 1.0, 1e-6);
            EXPECT_NEAR(canvas(row, col).green(), 0.0, 1e-6);
            EXPECT_NEAR(canvas(row, col).blue(), 0.0, 1e-6);
        }
    }
}

TEST(CanvasTests, AccessRowOutsideRange) {
    raytracer::drawing::Canvas<double> canvas(4, 3);
    EXPECT_THROW(canvas(4, 0), raytracer::exceptions::RowOutOfRangeException);
}

TEST(CanvasTests, AccessColOutsideRange) {
    raytracer::drawing::Canvas<double> canvas(4, 3);
    EXPECT_THROW(canvas(0, 4), raytracer::exceptions::ColumnOutOfRangeException);
}

TEST(CanvasTests, NonSquareBlueCanvas) {
    raytracer::drawing::Canvas<double> canvas(4, 3);

    for (size_t row = 0; row < canvas.height(); ++row) {
        for (size_t col = 0; col < canvas.width(); ++col) {
            canvas(row, col) = raytracer::drawing::Color(0.0, 0.0, 1.0);
        }
    }

    for (size_t row = 0; row < canvas.height(); ++row) {
        for (size_t col = 0; col < canvas.width(); ++col) {
            EXPECT_NEAR(canvas(row, col).red(), 0.0, 1e-6);
            EXPECT_NEAR(canvas(row, col).green(), 0.0, 1e-6);
            EXPECT_NEAR(canvas(row, col).blue(), 1.0, 1e-6);
        }
    }
}

TEST(MatrixTests, CreateMatrix) {
    raytracer::maths::Matrix<double> matrix(4, 4);

    matrix(0, 0) = 1.0;
    matrix(0, 1) = 2.0;
    matrix(0, 2) = 3.0;
    matrix(0, 3) = 4.0;
    matrix(1, 0) = 5.5;
    matrix(1, 1) = 6.5;
    matrix(1, 2) = 7.5;
    matrix(1, 3) = 8.5;
    matrix(2, 0) = 9.0;
    matrix(2, 1) = 10.0;
    matrix(2, 2) = 11.0;
    matrix(2, 3) = 12.0;
    matrix(3, 0) = 13.5;
    matrix(3, 1) = 14.5;
    matrix(3, 2) = 15.5;
    matrix(3, 3) = 16.5;

    EXPECT_NEAR(matrix(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(matrix(0, 1), 2.0, 1e-6);
    EXPECT_NEAR(matrix(0, 2), 3.0, 1e-6);
    EXPECT_NEAR(matrix(0, 3), 4.0, 1e-6);
    EXPECT_NEAR(matrix(1, 0), 5.5, 1e-6);
    EXPECT_NEAR(matrix(1, 1), 6.5, 1e-6);
    EXPECT_NEAR(matrix(1, 2), 7.5, 1e-6);
    EXPECT_NEAR(matrix(1, 3), 8.5, 1e-6);
    EXPECT_NEAR(matrix(2, 0), 9.0, 1e-6);
    EXPECT_NEAR(matrix(2, 1), 10.0, 1e-6);
    EXPECT_NEAR(matrix(2, 2), 11.0, 1e-6);
    EXPECT_NEAR(matrix(2, 3), 12.0, 1e-6);
    EXPECT_NEAR(matrix(3, 0), 13.5, 1e-6);
    EXPECT_NEAR(matrix(3, 1), 14.5, 1e-6);
    EXPECT_NEAR(matrix(3, 2), 15.5, 1e-6);
    EXPECT_NEAR(matrix(3, 3), 16.5, 1e-6);
}

TEST(MatrixTests, CreateIdentityMatrix)
{
    auto identity = raytracer::maths::Matrix<double>::identity(4);

    for (size_t row = 0; row < 4; ++row) {
        for (size_t col = 0; col < 4; ++col) {
            if (row == col) {
                EXPECT_NEAR(identity(row, col), 1.0, 1e-6);
            } else {
                EXPECT_NEAR(identity(row, col), 0.0, 1e-6);
            }
        }
    }
}

TEST(MatrixTests, CreateMatrixWithValues) {
    auto m = raytracer::maths::Matrix<double>(3, 4, {
        0, 1, 2, 3,
        4, 5, 6, 7,
        8, 9, 10, 11,
    });

    EXPECT_NEAR(m(0, 0), 0.0, 1e-6);
    EXPECT_NEAR(m(0, 1), 1.0, 1e-6);
    EXPECT_NEAR(m(0, 2), 2.0, 1e-6);
    EXPECT_NEAR(m(0, 3), 3.0, 1e-6);
    EXPECT_NEAR(m(1, 0), 4.0, 1e-6);
    EXPECT_NEAR(m(1, 1), 5.0, 1e-6);
    EXPECT_NEAR(m(1, 2), 6.0, 1e-6);
    EXPECT_NEAR(m(1, 3), 7.0, 1e-6);
    EXPECT_NEAR(m(2, 0), 8.0, 1e-6);
    EXPECT_NEAR(m(2, 1), 9.0, 1e-6);
    EXPECT_NEAR(m(2, 2), 10.0, 1e-6);
    EXPECT_NEAR(m(2, 3), 11.0, 1e-6);

    std::cout << m << std::endl;
}

TEST(MatrixTests, AddMatrices) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });
    auto m2 = raytracer::maths::Matrix<double>(2, 2, {
        5, 6,
        7, 8.
    });

    auto res1 = m1 + m2;

    EXPECT_NEAR(res1(0, 0), 6.0, 1e-6);
    EXPECT_NEAR(res1(0, 1), 8.0, 1e-6);
    EXPECT_NEAR(res1(1, 0), 10.0, 1e-6);
    EXPECT_NEAR(res1(1, 1), 12.0, 1e-6);

    EXPECT_EQ(res1.rows(), 2);
    EXPECT_EQ(res1.cols(), 2);

    auto res2 = m2 + m1;

    EXPECT_NEAR(res2(0, 0), 6.0, 1e-6);
    EXPECT_NEAR(res2(0, 1), 8.0, 1e-6);
    EXPECT_NEAR(res2(1, 0), 10.0, 1e-6);
    EXPECT_NEAR(res2(1, 1), 12.0, 1e-6);

    EXPECT_EQ(res2.rows(), 2);
    EXPECT_EQ(res2.cols(), 2);
}

TEST(MatrixTests, SubtractMatrices) {
    const auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });
    const auto m2 = raytracer::maths::Matrix<double>(2, 2, {
        5, 6,
        7, 8,
    });

    auto res1 = m1 - m2;

    EXPECT_NEAR(res1(0, 0), -4.0, 1e-6);
    EXPECT_NEAR(res1(0, 1), -4.0, 1e-6);
    EXPECT_NEAR(res1(1, 0), -4.0, 1e-6);
    EXPECT_NEAR(res1(1, 1), -4.0, 1e-6);

    EXPECT_EQ(res1.rows(), 2);
    EXPECT_EQ(res1.cols(), 2);

    auto res2 = m2 - m1;

    EXPECT_NEAR(res2(0, 0), 4.0, 1e-6);
    EXPECT_NEAR(res2(0, 1), 4.0, 1e-6);
    EXPECT_NEAR(res2(1, 0), 4.0, 1e-6);
    EXPECT_NEAR(res2(1, 1), 4.0, 1e-6);

    EXPECT_EQ(res2.rows(), 2);
    EXPECT_EQ(res2.cols(), 2);
}

TEST(MatrixTests, LeftMultByScalar) {
    const auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        4, 5,
    });
    auto res1 = 2 * m1;

    EXPECT_NEAR(res1(0, 0), 2.0, 1e-6);
    EXPECT_NEAR(res1(0, 1), 4.0, 1e-6);
    EXPECT_NEAR(res1(1, 0), 8.0, 1e-6);
    EXPECT_NEAR(res1(1, 1), 10.0, 1e-6);

    EXPECT_EQ(res1.rows(), 2);
    EXPECT_EQ(res1.cols(), 2);
}

TEST(MatrixTests, RightMultByScalar) {
    const auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        4, 5,
    });
    auto res1 = m1 * 2;

    EXPECT_NEAR(res1(0, 0), 2.0, 1e-6);
    EXPECT_NEAR(res1(0, 1), 4.0, 1e-6);
    EXPECT_NEAR(res1(1, 0), 8.0, 1e-6);
    EXPECT_NEAR(res1(1, 1), 10.0, 1e-6);

    EXPECT_EQ(res1.rows(), 2);
    EXPECT_EQ(res1.cols(), 2);
}

TEST(MatrixTests, DivByScalar) {
    const auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        4, 5,
    });
    auto res1 = m1 / 2;

    EXPECT_NEAR(res1(0, 0), 0.5, 1e-6);
    EXPECT_NEAR(res1(0, 1), 1.0, 1e-6);
    EXPECT_NEAR(res1(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(res1(1, 1), 2.5, 1e-6);

    EXPECT_EQ(res1.rows(), 2);
    EXPECT_EQ(res1.cols(), 2);
}

TEST(MatrixTests, CompoundAddTwoMatrices) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });
    const auto m2 = raytracer::maths::Matrix<double>(2, 2, {
        5, 6,
        7, 8,
    });

    m1 += m2;

    EXPECT_NEAR(m1(0, 0), 6.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 8.0, 1e-6);
    EXPECT_NEAR(m1(1, 0), 10.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 12.0, 1e-6);

    EXPECT_EQ(m1.rows(), 2);
    EXPECT_EQ(m1.cols(), 2);
}

TEST(MatrixTests, CompoundSubTwoMatrices) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });
    const auto m2 = raytracer::maths::Matrix<double>(2, 2, {
        5, 6,
        7, 8,
    });

    m1 -= m2;

    EXPECT_NEAR(m1(0, 0), -4.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), -4.0, 1e-6);
    EXPECT_NEAR(m1(1, 0), -4.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), -4.0, 1e-6);

    EXPECT_EQ(m1.rows(), 2);
    EXPECT_EQ(m1.cols(), 2);
}

TEST(MatrixTests, CompoundMultMatScalar) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });

    m1 *= 2.0;

    EXPECT_NEAR(m1(0, 0), 2.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 4.0, 1e-6);
    EXPECT_NEAR(m1(1, 0), 6.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 8.0, 1e-6);

    EXPECT_EQ(m1.rows(), 2);
    EXPECT_EQ(m1.cols(), 2);
}

TEST(MatrixTests, CompoundDivMatScalar) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });

    m1 /= 2.0;

    EXPECT_NEAR(m1(0, 0), 0.5, 1e-6);
    EXPECT_NEAR(m1(0, 1), 1.0, 1e-6);
    EXPECT_NEAR(m1(1, 0), 1.5, 1e-6);
    EXPECT_NEAR(m1(1, 1), 2.0, 1e-6);

    EXPECT_EQ(m1.rows(), 2);
    EXPECT_EQ(m1.cols(), 2);
}

TEST(MatrixTests, CompoundDivMatScalarByZero) {
    auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });

    EXPECT_THROW(m1 /= 0, std::invalid_argument);
}

TEST(MatrixTests, DivMatScalarByZero) {
    const auto m1 = raytracer::maths::Matrix<double>(2, 2, {
        1, 2,
        3, 4,
    });

    EXPECT_THROW(m1 / 0, std::invalid_argument);
}

TEST(MatrixTests, MatMulSameSize) {
    raytracer::maths::Matrix<double> m1(4, 4, {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    });

    raytracer::maths::Matrix<double> m2(4, 4, {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    });

    auto result = m1 * m2;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 20.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 22.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 50.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 48.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 44.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 54.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 114.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 108.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 68.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 86.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 178.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 168.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 92.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 118.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 242.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 228.0, 1e-6);

    result = m2 * m1;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 60.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 64.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 68.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 72.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 14.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 19.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 24.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 138.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 156.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 174.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 192.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 178.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 196.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 214.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 232.0, 1e-6);
}

TEST(MatrixTests, MatMulDifferentSizes) {
    raytracer::maths::Matrix<double> m1(4, 4, {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    });
    raytracer::maths::Matrix<double> m2(4, 5, {
        1, 2, 3, 4, 9,
        5, 6, 7, 8, 19,
        9, 10, 11, 12, 24,
        13, 14, 15, 16, 26,
    });

    auto result = m1 * m2;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 5);

    EXPECT_NEAR(result(0, 0), 60.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 64.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 68.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 72.0, 1e-6);
    EXPECT_NEAR(result(0, 4), 127.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 14.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 19.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 24.0, 1e-6);
    EXPECT_NEAR(result(1, 4), 63.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 138.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 156.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 174.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 192.0, 1e-6);
    EXPECT_NEAR(result(2, 4), 367.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 178.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 196.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 214.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 232.0, 1e-6);
    EXPECT_NEAR(result(3, 4), 423.0, 1e-6);
}

TEST(MatrixTests, MatMulDifferentSizes2) {
    raytracer::maths::Matrix<double> m1(4, 3, {
        -2, 1, 2,
        3, 2, 1,
        4, 3, 6,
        2, 9, 3
    });
    raytracer::maths::Matrix<double> m2(3, 4, {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
    });

    auto result = m1 * m2;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 21.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 22.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 23.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 24.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 22.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 28.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 34.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 40.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 73.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 86.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 99.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 112.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 74.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 88.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 102.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 116.0, 1e-6);

    auto result2 = m2 * m1;

    EXPECT_EQ(result2.rows(), 3);
    EXPECT_EQ(result2.cols(), 3);

    EXPECT_NEAR(result2(0, 0), 24.0, 1e-6);
    EXPECT_NEAR(result2(0, 1), 50.0, 1e-6);
    EXPECT_NEAR(result2(0, 2), 34.0, 1e-6);

    EXPECT_NEAR(result2(1, 0), 52.0, 1e-6);
    EXPECT_NEAR(result2(1, 1), 110.0, 1e-6);
    EXPECT_NEAR(result2(1, 2), 82.0, 1e-6);

    EXPECT_NEAR(result2(2, 0), 80.0, 1e-6);
    EXPECT_NEAR(result2(2, 1), 170.0, 1e-6);
    EXPECT_NEAR(result2(2, 2), 130.0, 1e-6);
}

TEST(MatrixTests, MatMulSizeMismatch) {
    raytracer::maths::Matrix<double> m1(3, 3, {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9,
    });
    raytracer::maths::Matrix<double> m2(4, 3, {
        -2, 1, 2,
        3, 2, 1,
        4, 3, 6,
        2, 9, 3
    });

    EXPECT_THROW(m1 * m2, raytracer::exceptions::ShapeMismatchException);
}

TEST(MatrixTests, MatMulIdentity) {
    raytracer::maths::Matrix<double> m1(4, 4, {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16,
    });
    auto identity = raytracer::maths::Matrix<double>::identity(4);

    auto result = identity * m1;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 2.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 3.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 4.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 5.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 6.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 7.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 8.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 9.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 10.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 11.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 12.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 13.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 14.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 15.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 16.0, 1e-6);

    result = m1 * identity;

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 2.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 3.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 4.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 5.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 6.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 7.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 8.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 9.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 10.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 11.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 12.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 13.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 14.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 15.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 16.0, 1e-6);
}

TEST(MatrixTests, CompoundMultMatSameSize) {
    raytracer::maths::Matrix<double> m1(4, 4, {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
});

    raytracer::maths::Matrix<double> m2(4, 4, {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    });

    m1 *= m2;

    EXPECT_EQ(m1.rows(), 4);
    EXPECT_EQ(m1.cols(), 4);

    EXPECT_NEAR(m1(0, 0), 20.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 22.0, 1e-6);
    EXPECT_NEAR(m1(0, 2), 50.0, 1e-6);
    EXPECT_NEAR(m1(0, 3), 48.0, 1e-6);

    EXPECT_NEAR(m1(1, 0), 44.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 54.0, 1e-6);
    EXPECT_NEAR(m1(1, 2), 114.0, 1e-6);
    EXPECT_NEAR(m1(1, 3), 108.0, 1e-6);

    EXPECT_NEAR(m1(2, 0), 68.0, 1e-6);
    EXPECT_NEAR(m1(2, 1), 86.0, 1e-6);
    EXPECT_NEAR(m1(2, 2), 178.0, 1e-6);
    EXPECT_NEAR(m1(2, 3), 168.0, 1e-6);

    EXPECT_NEAR(m1(3, 0), 92.0, 1e-6);
    EXPECT_NEAR(m1(3, 1), 118.0, 1e-6);
    EXPECT_NEAR(m1(3, 2), 242.0, 1e-6);
    EXPECT_NEAR(m1(3, 3), 228.0, 1e-6);
}

TEST(MatrixTests, CompoundMultMatSameSize2) {
    raytracer::maths::Matrix<double> m1(4, 4, {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
});

    raytracer::maths::Matrix<double> m2(4, 4, {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    });

    m2 *= m1;

    EXPECT_EQ(m2.rows(), 4);
    EXPECT_EQ(m2.cols(), 4);

    EXPECT_NEAR(m2(0, 0), 60.0, 1e-6);
    EXPECT_NEAR(m2(0, 1), 64.0, 1e-6);
    EXPECT_NEAR(m2(0, 2), 68.0, 1e-6);
    EXPECT_NEAR(m2(0, 3), 72.0, 1e-6);

    EXPECT_NEAR(m2(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(m2(1, 1), 14.0, 1e-6);
    EXPECT_NEAR(m2(1, 2), 19.0, 1e-6);
    EXPECT_NEAR(m2(1, 3), 24.0, 1e-6);

    EXPECT_NEAR(m2(2, 0), 138.0, 1e-6);
    EXPECT_NEAR(m2(2, 1), 156.0, 1e-6);
    EXPECT_NEAR(m2(2, 2), 174.0, 1e-6);
    EXPECT_NEAR(m2(2, 3), 192.0, 1e-6);

    EXPECT_NEAR(m2(3, 0), 178.0, 1e-6);
    EXPECT_NEAR(m2(3, 1), 196.0, 1e-6);
    EXPECT_NEAR(m2(3, 2), 214.0, 1e-6);
    EXPECT_NEAR(m2(3, 3), 232.0, 1e-6);


}

TEST(MatrixTests, CompoundMulDifferentSizes) {
    raytracer::maths::Matrix<double> m1(4, 4, {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    });
    raytracer::maths::Matrix<double> m2(4, 5, {
        1, 2, 3, 4, 9,
        5, 6, 7, 8, 19,
        9, 10, 11, 12, 24,
        13, 14, 15, 16, 26,
    });

    m1 *= m2;

    EXPECT_EQ(m1.rows(), 4);
    EXPECT_EQ(m1.cols(), 5);

    EXPECT_NEAR(m1(0, 0), 60.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 64.0, 1e-6);
    EXPECT_NEAR(m1(0, 2), 68.0, 1e-6);
    EXPECT_NEAR(m1(0, 3), 72.0, 1e-6);
    EXPECT_NEAR(m1(0, 4), 127.0, 1e-6);

    EXPECT_NEAR(m1(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 14.0, 1e-6);
    EXPECT_NEAR(m1(1, 2), 19.0, 1e-6);
    EXPECT_NEAR(m1(1, 3), 24.0, 1e-6);
    EXPECT_NEAR(m1(1, 4), 63.0, 1e-6);

    EXPECT_NEAR(m1(2, 0), 138.0, 1e-6);
    EXPECT_NEAR(m1(2, 1), 156.0, 1e-6);
    EXPECT_NEAR(m1(2, 2), 174.0, 1e-6);
    EXPECT_NEAR(m1(2, 3), 192.0, 1e-6);
    EXPECT_NEAR(m1(2, 4), 367.0, 1e-6);

    EXPECT_NEAR(m1(3, 0), 178.0, 1e-6);
    EXPECT_NEAR(m1(3, 1), 196.0, 1e-6);
    EXPECT_NEAR(m1(3, 2), 214.0, 1e-6);
    EXPECT_NEAR(m1(3, 3), 232.0, 1e-6);
    EXPECT_NEAR(m1(3, 4), 423.0, 1e-6);
}

TEST(MatrixTests, PointToColumnMatrix) {
    raytracer::maths::Point3D<double> p(1.0, 2.0, 4.0);
    auto mat = point_to_column_matrix(p);

    EXPECT_NEAR(mat(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(mat(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(mat(2, 0), 4.0, 1e-6);
    EXPECT_NEAR(mat(3, 0), 1.0, 1e-6);

    raytracer::maths::Point3D<double> result = point_from_column_matrix(mat);
    EXPECT_NEAR(result.x(), 1.0, 1e-6);
    EXPECT_NEAR(result.y(), 2.0, 1e-6);
    EXPECT_NEAR(result.z(), 4.0, 1e-6);
    EXPECT_NEAR(result.w(), 1.0, 1e-6);
}

TEST(MatrixTests, PointToRowMatrix) {
    raytracer::maths::Point3D<double> p(1.0, 2.0, 4.0);
    auto mat = point_to_row_matrix(p);

    EXPECT_NEAR(mat(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(mat(0, 1), 2.0, 1e-6);
    EXPECT_NEAR(mat(0, 2), 4.0, 1e-6);
    EXPECT_NEAR(mat(0, 3), 1.0, 1e-6);

    auto result = point_from_row_matrix(mat);
    EXPECT_NEAR(result.x(), 1.0, 1e-6);
    EXPECT_NEAR(result.y(), 2.0, 1e-6);
    EXPECT_NEAR(result.z(), 4.0, 1e-6);
    EXPECT_NEAR(result.w(), 1.0, 1e-6);
}

TEST(MatrixTests, MatrixPointMultiplication) {
    const raytracer::maths::Matrix<double> m1(4, 4, {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    });
    raytracer::maths::Point3D<double> p(1.0, 2.0, 3.0);

    const auto m2 = point_to_column_matrix(p);
    const auto result = m1 * m2;

    auto point_transformed = point_from_column_matrix(result);

    EXPECT_NEAR(point_transformed.x(), 18.0, 1e-6);
    EXPECT_NEAR(point_transformed.y(), 24.0, 1e-6);
    EXPECT_NEAR(point_transformed.z(), 33.0, 1e-6);
    EXPECT_NEAR(point_transformed.w(), 1.0, 1e-6);
}

TEST(MatrixTests, VectorToColumnMatrix) {
    const raytracer::maths::Vector3D<double> v(1.0, 2.0, 3.0);
    auto mat = vector_to_column_matrix(v);

    EXPECT_NEAR(mat(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(mat(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(mat(2, 0), 3.0, 1e-6);
    EXPECT_NEAR(mat(3, 0), 0.0, 1e-6);

    auto result = vector_from_column_matrix(mat);

    EXPECT_NEAR(result.x(), 1.0, 1e-6);
    EXPECT_NEAR(result.y(), 2.0, 1e-6);
    EXPECT_NEAR(result.z(), 3.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(MatrixTests, VectorToRowMatrix) {
    const raytracer::maths::Vector3D<double> v(1.0, 2.0, 3.0);
    auto mat = vector_to_row_matrix(v);

    EXPECT_NEAR(mat(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(mat(0, 1), 2.0, 1e-6);
    EXPECT_NEAR(mat(0, 2), 3.0, 1e-6);
    EXPECT_NEAR(mat(0, 3), 0.0, 1e-6);

    auto result = vector_from_row_matrix(mat);

    EXPECT_NEAR(result.x(), 1.0, 1e-6);
    EXPECT_NEAR(result.y(), 2.0, 1e-6);
    EXPECT_NEAR(result.z(), 3.0, 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(MatrixTests, TransposeMatrixDifferentSizes) {
    raytracer::maths::Matrix<double> m1(3, 2, {
        1, 2,
        3, 4,
        5, 6
    });

    auto result = transpose(m1);

    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 3);

    EXPECT_NEAR(result(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 3.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 5.0, 1e-6);
    EXPECT_NEAR(result(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 4.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 6.0, 1e-6);

    m1.transpose();

    EXPECT_EQ(m1.rows(), 2);
    EXPECT_EQ(m1.cols(), 3);

    EXPECT_NEAR(m1(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 3.0, 1e-6);
    EXPECT_NEAR(m1(0, 2), 5.0, 1e-6);
    EXPECT_NEAR(m1(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 4.0, 1e-6);
    EXPECT_NEAR(m1(1, 2), 6.0, 1e-6);
}

TEST(MatrixTests, TransposeMatrixDifferentSizes2) {
    raytracer::maths::Matrix<double> m1(3, 4, {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
    });

    auto result = transpose(m1);

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 3);

    EXPECT_NEAR(result(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 5.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 9.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 6.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 10.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 3.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 7.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 11.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 4.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 8.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 12.0, 1e-6);

    m1.transpose();

    EXPECT_EQ(m1.rows(), 4);
    EXPECT_EQ(m1.cols(), 3);

    EXPECT_NEAR(m1(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 5.0, 1e-6);
    EXPECT_NEAR(m1(0, 2), 9.0, 1e-6);

    EXPECT_NEAR(m1(1, 0), 2.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 6.0, 1e-6);
    EXPECT_NEAR(m1(1, 2), 10.0, 1e-6);

    EXPECT_NEAR(m1(2, 0), 3.0, 1e-6);
    EXPECT_NEAR(m1(2, 1), 7.0, 1e-6);
    EXPECT_NEAR(m1(2, 2), 11.0, 1e-6);

    EXPECT_NEAR(m1(3, 0), 4.0, 1e-6);
    EXPECT_NEAR(m1(3, 1), 8.0, 1e-6);
    EXPECT_NEAR(m1(3, 2), 12.0, 1e-6);
}

TEST(MatrixTests, TransposeSquaredMatrix) {
    raytracer::maths::Matrix<double> m1(4, 4, {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8
    });

    auto result = transpose(m1);

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 0.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 9.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 0.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 8.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 8.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 0.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 3.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 0.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 5.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 5.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 0.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 8.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 3.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 8.0, 1e-6);

    m1.transpose();

    EXPECT_EQ(m1.rows(), 4);
    EXPECT_EQ(m1.cols(), 4);

    EXPECT_NEAR(m1(0, 0), 0.0, 1e-6);
    EXPECT_NEAR(m1(0, 1), 9.0, 1e-6);
    EXPECT_NEAR(m1(0, 2), 1.0, 1e-6);
    EXPECT_NEAR(m1(0, 3), 0.0, 1e-6);

    EXPECT_NEAR(m1(1, 0), 9.0, 1e-6);
    EXPECT_NEAR(m1(1, 1), 8.0, 1e-6);
    EXPECT_NEAR(m1(1, 2), 8.0, 1e-6);
    EXPECT_NEAR(m1(1, 3), 0.0, 1e-6);

    EXPECT_NEAR(m1(2, 0), 3.0, 1e-6);
    EXPECT_NEAR(m1(2, 1), 0.0, 1e-6);
    EXPECT_NEAR(m1(2, 2), 5.0, 1e-6);
    EXPECT_NEAR(m1(2, 3), 5.0, 1e-6);

    EXPECT_NEAR(m1(3, 0), 0.0, 1e-6);
    EXPECT_NEAR(m1(3, 1), 8.0, 1e-6);
    EXPECT_NEAR(m1(3, 2), 3.0, 1e-6);
    EXPECT_NEAR(m1(3, 3), 8.0, 1e-6);


}

TEST(MatrixTests, TransposeIdentity) {
    auto m = raytracer::maths::Matrix<double>::identity(4);

    auto result = transpose(m);

    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);

    EXPECT_NEAR(result(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(result(0, 1), 0.0, 1e-6);
    EXPECT_NEAR(result(0, 2), 0.0, 1e-6);
    EXPECT_NEAR(result(0, 3), 0.0, 1e-6);

    EXPECT_NEAR(result(1, 0), 0.0, 1e-6);
    EXPECT_NEAR(result(1, 1), 1.0, 1e-6);
    EXPECT_NEAR(result(1, 2), 0.0, 1e-6);
    EXPECT_NEAR(result(1, 3), 0.0, 1e-6);

    EXPECT_NEAR(result(2, 0), 0.0, 1e-6);
    EXPECT_NEAR(result(2, 1), 0.0, 1e-6);
    EXPECT_NEAR(result(2, 2), 1.0, 1e-6);
    EXPECT_NEAR(result(2, 3), 0.0, 1e-6);

    EXPECT_NEAR(result(3, 0), 0.0, 1e-6);
    EXPECT_NEAR(result(3, 1), 0.0, 1e-6);
    EXPECT_NEAR(result(3, 2), 0.0, 1e-6);
    EXPECT_NEAR(result(3, 3), 1.0, 1e-6);

    m.transpose();

    EXPECT_EQ(m.rows(), 4);
    EXPECT_EQ(m.cols(), 4);

    EXPECT_NEAR(m(0, 0), 1.0, 1e-6);
    EXPECT_NEAR(m(0, 1), 0.0, 1e-6);
    EXPECT_NEAR(m(0, 2), 0.0, 1e-6);
    EXPECT_NEAR(m(0, 3), 0.0, 1e-6);

    EXPECT_NEAR(m(1, 0), 0.0, 1e-6);
    EXPECT_NEAR(m(1, 1), 1.0, 1e-6);
    EXPECT_NEAR(m(1, 2), 0.0, 1e-6);
    EXPECT_NEAR(m(1, 3), 0.0, 1e-6);

    EXPECT_NEAR(m(2, 0), 0.0, 1e-6);
    EXPECT_NEAR(m(2, 1), 0.0, 1e-6);
    EXPECT_NEAR(m(2, 2), 1.0, 1e-6);
    EXPECT_NEAR(m(2, 3), 0.0, 1e-6);

    EXPECT_NEAR(m(3, 0), 0.0, 1e-6);
    EXPECT_NEAR(m(3, 1), 0.0, 1e-6);
    EXPECT_NEAR(m(3, 2), 0.0, 1e-6);
    EXPECT_NEAR(m(3, 3), 1.0, 1e-6);
}