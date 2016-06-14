#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

int main()
{
    // input signal parameters
    const std::size_t SIZE = 64;
    const Quasar::FrequencyType sampleFreq = 2000, f1 = 125, f2 = 700;

    Quasar::SineGenerator sine1(sampleFreq);
    sine1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Quasar::SineGenerator sine2(sampleFreq);
    sine2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    auto sum = sine1 + sine2;

    Quasar::TextPlot plot("Input signal");
    plot.plot(sum);

    // calculate the FFT
    auto fft = Quasar::FftFactory::getFft(SIZE);
    Quasar::SpectrumType spectrum = fft->fft(sum.toArray());

    plot.setTitle("Spectrum");
    plot.plotSpectrum(spectrum);

    return 0;
}
