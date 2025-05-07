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

    dot_prod = dot<float>(v1, v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);
}

TEST(VectorTests, VectorDotProductDouble) {
    raytracer::maths::Vector3D<double> v1(1.0, 2.0, 3.0);
    raytracer::maths::Vector3D<double> v2(2.0, 3.0, 4.0);

    double dot_prod = v1.dot(v2);
    EXPECT_NEAR(dot_prod, 20.0, 1e-6);

    dot_prod = dot<double>(v1, v2);
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

    cross_prod_v1v2 = cross<float>(v1, v2);
    EXPECT_NEAR(cross_prod_v1v2.x(), -1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.y(), 2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v1v2.z(), -1.0, 1e-6);

    cross_prod_v2v1 = cross<double>(v2, v1);
    EXPECT_NEAR(cross_prod_v2v1.x(), 1.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.y(), -2.0, 1e-6);
    EXPECT_NEAR(cross_prod_v2v1.z(), 1.0, 1e-6);
}