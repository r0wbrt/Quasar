#include "aquila/global.h"
#include "aquila/filter/MelFilter.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>


SUITE(MelFilter)
{
    TEST(Roundtrip)
    {
        Quasar::FrequencyType frequency = 1000.0;
        auto melFrequency = Quasar::MelFilter::linearToMel(frequency);
        auto linearFrequency = Quasar::MelFilter::melToLinear(melFrequency);
        CHECK_CLOSE(frequency, linearFrequency, 0.00001);
    }

    TEST(SampleFrequency)
    {
        Quasar::FrequencyType sampleFrequency = 44100.0;
        Quasar::MelFilter filter(sampleFrequency);
        CHECK_EQUAL(sampleFrequency, filter.getSampleFrequency());
    }

    TEST(Assignment)
    {
        Quasar::FrequencyType sampleFrequency = 44100.0;
        Quasar::MelFilter filter(sampleFrequency);
        Quasar::MelFilter other(1000.0);
        other = filter;
        CHECK_EQUAL(44100.0, other.getSampleFrequency());
    }

    TEST(OutsideTriangle)
    {
        Quasar::FrequencyType sampleFrequency = 44100.0;
        const std::size_t N = 2048;

        // single spectral peak at highest frequency
        Quasar::SpectrumType spectrum(N);
        spectrum[N / 2 - 1] = 5000;

        // 0-th filter for lowest frequencies
        Quasar::MelFilter filter(sampleFrequency);
        filter.createFilter(0, 200, N);
        double output = filter.apply(spectrum);
        CHECK_CLOSE(0.0, output, 0.000001);
    }

    TEST(InsideTriangle)
    {
        Quasar::FrequencyType sampleFrequency = 44100.0;
        const std::size_t N = 2048;

        // create a single spectral peak at middle frequency of 0-th Mel filter
        Quasar::SpectrumType spectrum(N);
        Quasar::FrequencyType melFrequency = 100.0;
        Quasar::FrequencyType linearFrequency = Quasar::MelFilter::melToLinear(melFrequency);
        std::size_t peakNumber = N  * (linearFrequency / sampleFrequency);
        spectrum[peakNumber] = 5000.0;

        // 0-th filter for lowest frequencies
        Quasar::MelFilter filter(sampleFrequency);
        filter.createFilter(0, 200, N);
        double output = filter.apply(spectrum);
        CHECK_CLOSE(5000.0, output, 100);
    }
}
