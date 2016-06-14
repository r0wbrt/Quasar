#include "aquila/global.h"
#include "aquila/source/window/BlackmanHarrisWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(BlackmanHarrisWindow)
{
    TEST(ZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Quasar::BlackmanHarrisWindow w(SIZE);
        // 0.00006 has been manually calculated using:
        // 0.35875 - 0.48829 * cos(0) + 0.14128 * cos(0) - 0.01168 * cos(0)
        CHECK_CLOSE(0.00006, w.sample(0), 0.000001);
        CHECK_CLOSE(0.00006, w.sample(SIZE - 1), 0.000001);
    }

    TEST(Multiplication)
    {
        const std::size_t SIZE = 1024;
        Quasar::SquareGenerator generator(44100);
        generator.setFrequency(1000).setAmplitude(500).generate(SIZE);
        Quasar::BlackmanHarrisWindow w(SIZE);
        auto result = generator * w;
        // 0.03 = 0.00006 (see above) * 500 (amplitude)
        CHECK_CLOSE(0.03, result.sample(0), 0.000001);
        CHECK_CLOSE(0.03, result.sample(SIZE - 1), 0.000001);
    }
}

