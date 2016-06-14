#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include "UnitTest++/UnitTest++.h"

void testSpectrumPeaks(std::size_t SIZE,
                       Quasar::FrequencyType sampleFrequency,
                       Quasar::FrequencyType testFrequency)
{
    Quasar::SineGenerator generator(sampleFrequency);
    generator.setFrequency(testFrequency).setAmplitude(1).generate(SIZE);

    // divide into 4 frames
    const std::size_t samplesPerFrame = SIZE / 4;
    Quasar::FramesCollection frames(generator, samplesPerFrame);
    CHECK_EQUAL(4u, frames.count());

    Quasar::Spectrogram spectrogram(frames);

    // check all frames for a single spectral peak coming from the sine
    std::size_t halfLength = samplesPerFrame / 2;
    std::size_t expectedPeak = testFrequency * samplesPerFrame / sampleFrequency;
    std::vector<double> expected(halfLength);
    expected[expectedPeak] = halfLength * 1.0;
    for (std::size_t x = 0; x < spectrogram.getFrameCount(); ++x)
    {
        std::vector<double> absSpectrum(halfLength);
        for (std::size_t y = 0; y < halfLength; ++y)
        {
            absSpectrum[y] = std::abs(spectrogram.getPoint(x, y));
        }
        CHECK_ARRAY_CLOSE(expected, absSpectrum, halfLength, 0.00001);
    }
}


SUITE(Spectrogram)
{
    const std::size_t SIZE = 512;
    Quasar::FrequencyType sampleFrequency = 1024;

    TEST(Dimensions)
    {
        Quasar::SineGenerator generator(sampleFrequency);
        generator.setFrequency(32).setAmplitude(1).generate(SIZE);

        // divide into 4 frames, 128 samples each
        Quasar::FramesCollection frames(generator, SIZE / 4);
        CHECK_EQUAL(4u, frames.count());

        Quasar::Spectrogram spectrogram(frames);
        CHECK_EQUAL(frames.count(), spectrogram.getFrameCount());
        CHECK_EQUAL(frames.frame(0).length(), spectrogram.getSpectrumSize());
    }

    TEST(SpectrumPeaks)
    {
        testSpectrumPeaks(256, 1024, 32);
        testSpectrumPeaks(1024, 1024, 32);
        testSpectrumPeaks(4096, 1024, 32);
    }
}
