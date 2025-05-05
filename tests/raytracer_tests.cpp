#include <gtest/gtest.h>
#include <boost/math/special_functions/next.hpp>
#include "../include/maths.hpp"

TEST(FPTests, ApproximatelyEqualEpsilonAddSmall) {
    float a = 0.0;
    float b = 0.0;

    for (unsigned int i = 0; i < 10000; i++) {
        a += 0.001;
        b += 0.001;
        bool almostEqualEpsilon = raytracer::maths::AlmostEqualEpsilon(a, b);
        EXPECT_TRUE(almostEqualEpsilon);
    }
}

TEST(FPTests, ApproximatelyEqualEpsilonMultiplySmall) {
    float a = 0.01;
    float b = 0.01;

    for (unsigned int i = 0; i < 10000; i++) {
        a *= 0.001;
        b *= 0.001;
        bool almostEqualEpsilon = raytracer::maths::AlmostEqualEpsilon(a, b);
        EXPECT_TRUE(almostEqualEpsilon);
    }
}

TEST(PointTests, CreatePoint) {
    raytracer::maths::Point3D point(0, 0, 0);
    EXPECT_EQ(point.x(), 0);
    EXPECT_EQ(point.y(), 0);
    EXPECT_EQ(point.z(), 0);
    EXPECT_EQ(point.w(), 1);
}

TEST(PointTests, MovePointWithRightVectorAdd) {
    raytracer::maths::Vector3D v(1, 2, 3);
    raytracer::maths::Point3D p(1, 2, 3);

    auto new_p = p + v;

    EXPECT_EQ(new_p.x(), 2);
    EXPECT_EQ(new_p.y(), 4);
    EXPECT_EQ(new_p.z(), 6);
    EXPECT_EQ(new_p.w(), 1);
}

TEST(PointTests, MovePointWithLeftVectorAdd) {
    raytracer::maths::Vector3D v(1, 2, 3);
    raytracer::maths::Point3D p(1, 2, 3);

    auto new_p = v + p;

    EXPECT_EQ(new_p.x(), 2);
    EXPECT_EQ(new_p.y(), 4);
    EXPECT_EQ(new_p.z(), 6);
    EXPECT_EQ(new_p.w(), 1);
}

TEST(PointTests, MovePointBackward) {
    raytracer::maths::Vector3D v(5, 6, 7);
    raytracer::maths::Point3D p(3, 2, 1);
    auto new_p = p - v;

    EXPECT_EQ(new_p.x(), -2);
    EXPECT_EQ(new_p.y(), -4);
    EXPECT_EQ(new_p.z(), -6);
    EXPECT_EQ(new_p.w(), 1);
}

TEST(PointTests, ChangePoint) {
    raytracer::maths::Point3D point(1, 2, 3);
    point.x() = 2;
    point.y() = 4;
    point.z() = 8;
    EXPECT_EQ(point.x(), 2);
    EXPECT_EQ(point.y(), 4);
    EXPECT_EQ(point.z(), 8);
    EXPECT_EQ(point.w(), 1);
}

TEST(VectorTests, CreateVector) {
    raytracer::maths::Vector3D vector(0, 0, 0);
    EXPECT_EQ(vector.x(), 0);
    EXPECT_EQ(vector.y(), 0);
    EXPECT_EQ(vector.z(), 0);
    EXPECT_EQ(vector.w(), 0);
}

TEST(VectorTests, ChangeVector) {
    raytracer::maths::Vector3D vector(1, 2, 3);
    vector.x() = 2;
    vector.y() = 4;
    vector.z() = 8;
    EXPECT_EQ(vector.x(), 2);
    EXPECT_EQ(vector.y(), 4);
    EXPECT_EQ(vector.z(), 8);
    EXPECT_EQ(vector.w(), 0);
}

TEST(VectorTests, AddTwoVectors) {
    raytracer::maths::Vector3D v1(1, 2, 3);
    raytracer::maths::Vector3D v2(2, 4, 4);
    auto result = v1 + v2;
    EXPECT_EQ(result.x(), 3);
    EXPECT_EQ(result.y(), 6);
    EXPECT_EQ(result.z(), 7);
    EXPECT_EQ(result.w(), 0);
}

TEST(VectorTests, SubTwoVectors) {
    raytracer::maths::Vector3D v1(1, 2, 3);
    raytracer::maths::Vector3D v2(2, 4, 4);
    auto result = v1 - v2;
    EXPECT_EQ(result.x(), -1);
    EXPECT_EQ(result.y(), -2);
    EXPECT_EQ(result.z(), -1);
    EXPECT_EQ(result.w(), 0);
}

TEST(VectorTests, LeftMultByScalar) {
    raytracer::maths::Vector3D v(1, 2, 3);
    auto result = 2 * v;
    EXPECT_EQ(result.x(), 2);
    EXPECT_EQ(result.y(), 4);
    EXPECT_EQ(result.z(), 6);
    EXPECT_EQ(result.w(), 0);
}

TEST(VectorTests, RightMultByScalar) {
    raytracer::maths::Vector3D v(1, 2, 3);
    auto result = v * 2;
    EXPECT_EQ(result.x(), 2);
    EXPECT_EQ(result.y(), 4);
    EXPECT_EQ(result.z(), 6);
    EXPECT_EQ(result.w(), 0);
}

TEST(VectorTests, CompoundAddTwoVectors) {
    raytracer::maths::Vector3D v1(1, 2, 3);
    raytracer::maths::Vector3D v2(2, 4, 4);
    v1 += v2;
    EXPECT_EQ(v1.x(), 3);
    EXPECT_EQ(v1.y(), 6);
    EXPECT_EQ(v1.z(), 7);
    EXPECT_EQ(v1.w(), 0);
}

TEST(VectorTests, CompoundSubTwoVectors) {
    raytracer::maths::Vector3D v1(1, 2, 3);
    raytracer::maths::Vector3D v2(2, 4, 4);
    v1 -= v2;
    EXPECT_EQ(v1.x(), -1);
    EXPECT_EQ(v1.y(), -2);
    EXPECT_EQ(v1.z(), -1);
    EXPECT_EQ(v1.w(), 0);
}

TEST(VectorTests, CompoundMultVectorScalar) {
    raytracer::maths::Vector3D v(1, 2, 3);
    v *= 2;
    EXPECT_EQ(v.x(), 2);
    EXPECT_EQ(v.y(), 4);
    EXPECT_EQ(v.z(), 6);
    EXPECT_EQ(v.w(), 0);
}

TEST(VectorTests, GetVectorFromPointSubtraction) {
    raytracer::maths::Point3D v1(3, 2, 1);
    raytracer::maths::Point3D v2(5, 6, 7);
    auto result = v1 - v2;

    EXPECT_EQ(result.x(), -2);
    EXPECT_EQ(result.y(), -4);
    EXPECT_EQ(result.z(), -6);
    EXPECT_EQ(result.w(), 0);
}

TEST(VectorTests, NegateVector) {
    raytracer::maths::Vector3D v(1, -2, 1);
    -v;
    EXPECT_EQ(v.x(), -1);
    EXPECT_EQ(v.y(), 2);
    EXPECT_EQ(v.z(), -1);
    EXPECT_EQ(v.w(), 0);
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
    raytracer::maths::Vector3D v(1, 0, 0);
    auto length = v.length<float>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble) {
    raytracer::maths::Vector3D v(1, 0, 0);
    auto length = v.length<double>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat2) {
    raytracer::maths::Vector3D v(0, 1, 0);
    auto length = v.length<float>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble2) {
    raytracer::maths::Vector3D v(0, 1, 0);
    auto length = v.length<double>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat3) {
    raytracer::maths::Vector3D v(0, 0, 1);
    auto length = v.length<float>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthDouble3) {
    raytracer::maths::Vector3D v(0, 0, 1);
    auto length = v.length<double>();
    EXPECT_NEAR(length, 1.0, 1e-6);
}

TEST(VectorTests, VectorLengthFloat4) {
    raytracer::maths::Vector3D v(1, 2, 3);
    auto length = v.length<float>();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthDouble4) {
    raytracer::maths::Vector3D v(1, 2, 3);
    auto length = v.length<double>();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthFloat5) {
    raytracer::maths::Vector3D v(-1, -2, -3);
    auto length = v.length<float>();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, VectorLengthDouble5) {
    raytracer::maths::Vector3D v(-1, -2, -3);
    auto length = v.length<double>();
    EXPECT_NEAR(length, std::sqrt(14), 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionFloat) {
    raytracer::maths::Vector3D v(4, 0, 0);
    v.normalize<float>();
    EXPECT_NEAR(v.length<float>(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), 1.0, 1e-6);
    EXPECT_NEAR(v.y(), 0.0, 1e-6);
    EXPECT_NEAR(v.z(), 0.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionDouble) {
    raytracer::maths::Vector3D v(4, 0, 0);
    v.normalize<double>();
    EXPECT_NEAR(v.length<double>(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), 1.0, 1e-6);
    EXPECT_NEAR(v.y(), 0.0, 1e-6);
    EXPECT_NEAR(v.z(), 0.0, 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionFloat2) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    v.normalize<float>();
    EXPECT_NEAR(v.length<float>(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithMemberFunctionDouble2) {
    raytracer::maths::Vector3D v(1.0, 2.0, 3.0);
    v.normalize<double>();
    EXPECT_NEAR(v.length<double>(), 1.0, 1e-6);
    EXPECT_NEAR(v.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(v.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithFreeFunctionFloat) {
    raytracer::maths::Vector3D<float> v(1.0, 2.0, 3.0);
    auto result = normalize<float>(v);
    EXPECT_NEAR(result.length<float>(), 1.0, 1e-6);
    EXPECT_NEAR(result.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}

TEST(VectorTests, NormalizeVectorWithFreeFunctionDouble2) {
    raytracer::maths::Vector3D<double> v(1.0, 2.0, 3.0);
    auto result = normalize<double>(v);
    EXPECT_NEAR(result.length<double>(), 1.0, 1e-6);
    EXPECT_NEAR(result.x(), (1.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.y(), (2.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.z(), (3.0 / std::sqrt(14)), 1e-6);
    EXPECT_NEAR(result.w(), 0.0, 1e-6);
}