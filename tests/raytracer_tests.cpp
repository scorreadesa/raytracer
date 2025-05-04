#include <gtest/gtest.h>
#include <boost/math/special_functions/next.hpp>
#include "../include/maths.hpp"

TEST(HelloTest, BasicAssertions) {
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}

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

TEST(PointTests, CreatePoint) {
    raytracer::maths::Point3D point(0, 0, 0);
    EXPECT_EQ(point.x(), 0);
    EXPECT_EQ(point.y(), 0);
    EXPECT_EQ(point.z(), 0);
    EXPECT_EQ(point.w(), 1);
}


TEST(VectorTests, CreateVector) {
    raytracer::maths::Vector3D vector(0, 0, 0);
    EXPECT_EQ(vector.x(), 0);
    EXPECT_EQ(vector.y(), 0);
    EXPECT_EQ(vector.z(), 0);
    EXPECT_EQ(vector.w(), 0);
}