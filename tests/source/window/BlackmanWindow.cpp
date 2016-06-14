#include "aquila/global.h"
#include "aquila/source/window/BlackmanWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(BlackmanWindow)
{
    TEST(ZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Quasar::BlackmanWindow w(SIZE);
        CHECK_CLOSE(0.0, w.sample(0), 0.000001);
        CHECK_CLOSE(0.0, w.sample(SIZE - 1), 0.000001);
    }

    TEST(Multiplication)
    {
        const std::size_t SIZE = 1024;
        Quasar::SquareGenerator generator(44100);
        generator.setFrequency(1000).setAmplitude(500).generate(SIZE);
        Quasar::BlackmanWindow w(SIZE);
        auto result = generator * w;
        CHECK_CLOSE(0.0, result.sample(0), 0.000001);
        CHECK_CLOSE(0.0, result.sample(SIZE - 1), 0.000001);
    }
}

