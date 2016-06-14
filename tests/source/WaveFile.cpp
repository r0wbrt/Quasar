#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/WaveFile.h"
#include "aquila/source/FramesCollection.h"
#include "constants.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>


SUITE(WaveFile)
{
    TEST(Filename)
    {
        std::string filename(Aquila_TEST_WAVEFILE_8B_MONO);
        Quasar::WaveFile wav(filename);
        CHECK(filename == wav.getFilename());
    }

    TEST(AudioLength)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(103u, wav.getAudioLength());
    }

    TEST(BitsPerSample8)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(8, wav.getBitsPerSample());
    }

    TEST(BitsPerSample16)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(16u, wav.getBitsPerSample());
    }

    TEST(BytesPerSample8Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1u, wav.getBytesPerSample());
    }

    TEST(BytesPerSample8Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2u, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(2u, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4u, wav.getBytesPerSample());
    }

    TEST(OtherStereoChannel)
    {
        Quasar::WaveFile wavLeft(Aquila_TEST_WAVEFILE_16B_STEREO);
        Quasar::WaveFile wavRight(Aquila_TEST_WAVEFILE_16B_STEREO, Quasar::RIGHT);
        CHECK_EQUAL(wavLeft.getSamplesCount(), wavRight.getSamplesCount());
    }

    TEST(BytesPerSecond)
    {
        std::vector<std::string> filenames;
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_STEREO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_STEREO);
        std::for_each(
            std::begin(filenames),
            std::end(filenames),
            [] (std::string filename) {
                Quasar::WaveFile wav(filename);
                unsigned int expected = static_cast<unsigned int>(
                    wav.getSampleFrequency() * wav.getBytesPerSample()
                );
                CHECK_EQUAL(expected, wav.getBytesPerSec());
            }
        );
    }

    TEST(Channels8Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels8Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
    }

    TEST(Channels16Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels16Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
    }

    TEST(SampleFrequency)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(44100, wav.getSampleFrequency());
    }

    TEST(WaveSize8Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552u, wav.getWaveSize());
    }

    TEST(WaveSize16Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(18208u, wav.getWaveSize());
    }

    TEST(SamplesCount8Mono)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552u, wav.getSamplesCount());
    }

    TEST(SamplesCount16Stereo)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4552u, wav.getSamplesCount());
    }

    TEST(ToArray)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        const Quasar::SampleType* arr = wav.toArray();
        CHECK_EQUAL(wav.sample(0), arr[0]);
    }

    TEST(FramesCount1)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 0, 0);
        CHECK_EQUAL(0u, frames.count());
    }

    TEST(FramesCount2)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 10, 0);
        CHECK_EQUAL(10u, frames.count());
    }

    TEST(FramesCount3)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 20, 0);
        CHECK_EQUAL(5u, frames.count());
    }

    TEST(FramesCount4)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 0, 0.5);
        CHECK_EQUAL(0u, frames.count());
    }

    TEST(FramesCount5)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 10, 0.5);
        CHECK_EQUAL(19u, frames.count());
    }

    TEST(FramesCount6)
    {
        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Quasar::FramesCollection::createFromDuration(wav, 20, 0.66);
        CHECK_EQUAL(13u, frames.count());
    }

    TEST(Save8bit)
    {
        Quasar::WaveFile inputWav(Aquila_TEST_WAVEFILE_8B_MONO);
        Quasar::WaveFile::save(inputWav, Aquila_TEST_WAVEFILE_OUTPUT);

        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(inputWav.getSampleFrequency(), wav.getSampleFrequency());
        CHECK_EQUAL(8, wav.getBitsPerSample());
        CHECK_EQUAL(inputWav.getSamplesCount(), wav.getSamplesCount());
    }

    TEST(Save16bit)
    {
        Quasar::WaveFile inputWav(Aquila_TEST_WAVEFILE_16B_MONO);
        Quasar::WaveFile::save(inputWav, Aquila_TEST_WAVEFILE_OUTPUT);

        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(inputWav.getSampleFrequency(), wav.getSampleFrequency());
        CHECK_EQUAL(16, wav.getBitsPerSample());
        CHECK_EQUAL(inputWav.getSamplesCount(), wav.getSamplesCount());
    }

    TEST(SaveArray)
    {
        const std::size_t SIZE = 10;
        Quasar::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Quasar::SignalSource data(testArray, SIZE, 22050);
        Quasar::WaveFile::save(data, Aquila_TEST_WAVEFILE_OUTPUT);

        Quasar::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(22050, wav.getSampleFrequency());
        CHECK_EQUAL(16, wav.getBitsPerSample());
        CHECK_EQUAL(SIZE, wav.getSamplesCount());
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            CHECK_EQUAL(testArray[i], wav.sample(i));
        }
    }
}
