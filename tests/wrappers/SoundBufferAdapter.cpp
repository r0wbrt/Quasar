#include "aquila/source/generator/SineGenerator.h"
#include "aquila/wrappers/SoundBufferAdapter.h"
#include "UnitTest++/UnitTest++.h"


SUITE(SoundBufferAdapter)
{
    TEST(Empty)
    {
        Quasar::SoundBufferAdapter buffer;
        CHECK_EQUAL(0u, buffer.getSampleCount());
    }

    TEST(NumSamples)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Quasar::SoundBufferAdapter buffer(generator);
        CHECK_EQUAL(generator.length(), buffer.getSampleCount());
    }

    TEST(SampleFrequency)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Quasar::SoundBufferAdapter buffer(generator);
        CHECK_EQUAL(static_cast<unsigned int>(generator.getSampleFrequency()), buffer.getSampleRate());
    }

    TEST(Copy)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Quasar::SoundBufferAdapter buffer(generator);
        Quasar::SoundBufferAdapter buffer2(buffer);
        CHECK_EQUAL(generator.length(), buffer2.getSampleCount());
    }
}
