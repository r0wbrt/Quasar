#include "aquila/global.h"
#include "aquila/functions.h"
#include "UnitTest++/UnitTest++.h"
#include <vector>


SUITE(Functions)
{
    const std::size_t SIZE = 3;
    double arr1[SIZE] = {0, 1, 2};
    std::vector<double> v1(arr1, arr1 + SIZE);
    double arr2[SIZE] = {1, 2, 3};
    std::vector<double> v2(arr2, arr2 + SIZE);

    TEST(DecibelConversion)
    {
        double decibel = Quasar::dB(10.0);
        CHECK_CLOSE(20.0, decibel, 0.000001);
    }

    TEST(ComplexDecibelConversion)
    {
        double decibel = Quasar::dB(Quasar::ComplexType(0.0, 10.0));
        CHECK_CLOSE(20.0, decibel, 0.000001);
    }

    TEST(ReferenceDecibelConversion)
    {
        double decibel = Quasar::dB(1000.0, 10.0);
        CHECK_CLOSE(40.0, decibel, 0.000001);
    }

    TEST(ClampToMax)
    {
        double value = Quasar::clamp(5.0, 9.0, 6.0);
        CHECK_CLOSE(6.0, value, 0.000001);
    }

    TEST(ClampToMin)
    {
        double value = Quasar::clamp(5.0, 1.0, 6.0);
        CHECK_CLOSE(5.0, value, 0.000001);
    }

    TEST(ClampUnchanged)
    {
        double value = Quasar::clamp(5.0, 5.5, 6.0);
        CHECK_CLOSE(5.5, value, 0.000001);
    }

    TEST(RandomRange)
    {
        for (std::size_t i = 0; i < 1000; ++i)
        {
            int x = Quasar::random(1, 2);
            CHECK_EQUAL(1, x);
        }
    }

    TEST(RandomDoubleRange)
    {
        for (std::size_t i = 0; i < 1000; ++i)
        {
            double x = Quasar::randomDouble();
            CHECK(x < 1.0);
        }
    }

    TEST(IsPowerOf2ForNonPowers)
    {
        CHECK(!Quasar::isPowerOf2(0));
        CHECK(!Quasar::isPowerOf2(3));
        CHECK(!Quasar::isPowerOf2(15));
        CHECK(!Quasar::isPowerOf2(247));
        CHECK(!Quasar::isPowerOf2(32769));
    }

    TEST(IsPowerOf2ForPowers)
    {
        CHECK(Quasar::isPowerOf2(1));
        CHECK(Quasar::isPowerOf2(2));
        CHECK(Quasar::isPowerOf2(16));
        CHECK(Quasar::isPowerOf2(1024));
        CHECK(Quasar::isPowerOf2(32768));
        CHECK(Quasar::isPowerOf2(1152921504606846976ul));
    }

    TEST(NextPowerOf2)
    {
        CHECK_EQUAL(2, Quasar::nextPowerOf2(1));
        CHECK_EQUAL(4, Quasar::nextPowerOf2(3));
        CHECK_EQUAL(1024, Quasar::nextPowerOf2(513));
        CHECK_EQUAL(16384, Quasar::nextPowerOf2(10000));
        CHECK_EQUAL(65536, Quasar::nextPowerOf2(44100));
        CHECK_EQUAL(1152921504606846976ul, Quasar::nextPowerOf2(576460752303423489ul));
    }

    TEST(EuclideanDistanceToItself)
    {
        double distance = Quasar::euclideanDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(EuclideanDistance)
    {
        double distance = Quasar::euclideanDistance(v1, v2);
        CHECK_CLOSE(1.732051, distance, 0.000001);
    }

    TEST(ManhattanDistanceToItself)
    {
        double distance = Quasar::manhattanDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(ManhattanDistance)
    {
        double distance = Quasar::manhattanDistance(v1, v2);
        CHECK_CLOSE(3.0, distance, 0.000001);
    }

    TEST(ChebyshevDistanceToItself)
    {
        double distance = Quasar::chebyshevDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(ChebyshevDistance)
    {
        double distance = Quasar::chebyshevDistance(v1, v2);
        CHECK_CLOSE(1.0, distance, 0.000001);
    }

}
