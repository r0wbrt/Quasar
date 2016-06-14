#include "aquila/global.h"
#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>

SUITE(WhiteNoiseGenerator)
{
    // sample frequency is fixed at 1 kHz
    Quasar::WhiteNoiseGenerator gen(1000);

    TEST(DoesNotOverrunAplitude)
    {
        std::srand(std::time(0));
        Quasar::SampleType amplitude = 1000;
        gen.setAmplitude(amplitude).generate(2048);
        auto result = std::minmax_element(std::begin(gen), std::end(gen));
        CHECK(*result.first > -amplitude);
        CHECK(*result.second < amplitude);
    }

    TEST(ZeroMean)
    {
        std::srand(std::time(0));
        gen.setAmplitude(1).generate(2048);
        auto mean = Quasar::mean(gen);
        CHECK_CLOSE(0.0, mean, 0.1);
    }
}
