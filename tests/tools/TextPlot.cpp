#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/tools/TextPlot.h"
#include "aquila/transform/FftFactory.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>
#include <sstream>
#include <vector>


SUITE(TextPlot)
{
    auto expectedSinePlot =
        "\nData plot\n"
        "   ***             ***             ***             ***          \n"
        "                                                                \n"
        "  *   *           *   *           *   *           *   *         \n"
        "                                                                \n"
        " *     *         *     *         *     *         *     *        \n"
        "                                                                \n"
        "                                                                \n"
        "        *               *               *               *       \n"
        "*               *               *               *               \n"
        "                                                                \n"
        "                                                                \n"
        "         *     *         *     *         *     *         *     *\n"
        "                                                                \n"
        "          *   *           *   *           *   *           *   * \n"
        "                                                                \n"
        "           ***             ***             ***             ***  \n";

    auto expectedSpectrum =
        "\nSpectrum\n"
        "    *                           \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "                                \n"
        "**** ***************************\n";

    TEST(DefaultTitle)
    {
        Quasar::TextPlot plot;
        CHECK_EQUAL(plot.getTitle(), "Data plot");
    }

    TEST(CustomTitle)
    {
        Quasar::TextPlot plot;
        plot.setTitle("My plot");
        CHECK_EQUAL(plot.getTitle(), "My plot");
    }

    TEST(DefaultSize)
    {
        Quasar::TextPlot plot;
        CHECK_EQUAL(plot.getWidth(), 64u);
        CHECK_EQUAL(plot.getHeight(), 16u);
    }

    TEST(CustomSize)
    {
        Quasar::TextPlot plot;
        plot.setSize(80, 12);
        CHECK_EQUAL(plot.getWidth(), 80u);
        CHECK_EQUAL(plot.getHeight(), 12u);
    }

    TEST(PlotSineWave)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        std::stringstream out;
        Quasar::TextPlot plot("Data plot", out);
        plot.plot(generator);
        CHECK_EQUAL(expectedSinePlot, out.str());
    }

    TEST(PlotSineWaveFromArray)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        std::stringstream out;
        Quasar::TextPlot plot("Data plot", out);
        plot.plot(generator.toArray(), generator.length());
        CHECK_EQUAL(expectedSinePlot, out.str());
    }

    TEST(PlotSineWaveFromVector)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        auto arr = generator.toArray();
        std::vector<double> vec(arr, arr + generator.length());
        std::stringstream out;
        Quasar::TextPlot plot("Data plot", out);
        plot.plot(vec);
        CHECK_EQUAL(expectedSinePlot, out.str());
    }

    TEST(PlotSpectrum)
    {
        Quasar::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        auto fft = Quasar::FftFactory::getFft(generator.length());
        Quasar::SpectrumType spectrum = fft->fft(generator.toArray());
        std::stringstream out;
        Quasar::TextPlot plot("Spectrum", out);
        plot.plotSpectrum(spectrum);
        CHECK_EQUAL(expectedSpectrum, out.str());
    }
}
