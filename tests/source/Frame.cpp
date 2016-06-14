#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/Frame.h"
#include "UnitTest++/UnitTest++.h"


SUITE(Frame)
{
    const int SIZE = 10;
    Quasar::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Quasar::SignalSource data(testArray, SIZE, 22050);

    TEST(BitsPerSample)
    {
        Quasar::Frame frame(data, 0, 1);
        CHECK_EQUAL(8 * sizeof(Quasar::SampleType), frame.getBitsPerSample());
    }

    TEST(SampleFrequency)
    {
        Quasar::Frame frame(data, 0, 1);
        CHECK_EQUAL(data.getSampleFrequency(), frame.getSampleFrequency());
    }

    TEST(Copying)
    {
        Quasar::Frame frame(data, 0, 3);
        Quasar::Frame frameCopy(frame);
        CHECK_EQUAL(3u, frameCopy.getSamplesCount());
        CHECK_EQUAL(2, frameCopy.sample(2));
    }

    TEST(Assignment)
    {
        Quasar::Frame frame(data, 0, 3);
        Quasar::Frame otherFrame(data, 3, 6);
        otherFrame = frame;
        CHECK_EQUAL(3u, otherFrame.getSamplesCount());
        CHECK_EQUAL(2, otherFrame.sample(2));
    }

    TEST(ArrayOffset)
    {
        Quasar::Frame frame(data, 5, 8);
        const Quasar::SampleType* frameArray = frame.toArray();
        CHECK_EQUAL(5, frameArray - data.toArray());
    }

    TEST(Sample1)
    {
        Quasar::Frame frame(data, 0, 10);
        CHECK_EQUAL(0, frame.sample(0));
    }

    TEST(Sample2)
    {
        Quasar::Frame frame(data, 1, 10);
        CHECK_EQUAL(1, frame.sample(0));
    }

    TEST(Sample3)
    {
        Quasar::Frame frame(data, 2, 10);
        CHECK_EQUAL(4, frame.sample(2));
    }

    TEST(Sample4)
    {
        Quasar::Frame frame(data, 9, 10);
        CHECK_EQUAL(9, frame.sample(0));
    }

    TEST(Sample5)
    {
        Quasar::Frame frame(data, 6, 7);
        CHECK_EQUAL(7, frame.sample(1));
    }

    TEST(SampleCount1)
    {
        Quasar::Frame frame(data, 0, 1);
        CHECK_EQUAL(1u, frame.getSamplesCount());
    }

    TEST(SampleCount2)
    {
        Quasar::Frame frame(data, 0, 4);
        CHECK_EQUAL(4u, frame.getSamplesCount());
    }

    TEST(SampleCount3)
    {
        Quasar::Frame frame(data, 0, 10);
        CHECK_EQUAL(10u, frame.getSamplesCount());
    }

    TEST(SampleCount4)
    {
        Quasar::Frame frame(data, 0, 15);
        CHECK_EQUAL(10u, frame.getSamplesCount());
    }

    TEST(SampleCount5)
    {
        Quasar::Frame frame(data, 9, 20);
        CHECK_EQUAL(1u, frame.getSamplesCount());
    }
}
