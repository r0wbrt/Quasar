#include "aquila/global.h"
#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "aquila/transform/Dft.h"
#include "aquila/transform/AquilaFft.h"
#include "aquila/transform/OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>

double difference(Quasar::SpectrumType correct, Quasar::SpectrumType checked)
{
    double val = 0.0;
    for (std::size_t i = 0; i < correct.size(); ++i)
    {
        val += std::abs(correct[i] - checked[i]);
    }

    return std::abs(val);
}

int main()
{
    const Quasar::FrequencyType sampleFrequency = 8000.0;

    std::cout << "    N    |    Aquila FFT    |     Ooura      \n"
                 "---------+------------------+----------------\n";
    for (int power = 1; power <= 10; ++power)
    {
        std::size_t N = 1 << power;
        Quasar::WhiteNoiseGenerator source(sampleFrequency);
        source.setAmplitude(1024).generate(N);

        // reference spectrum calculated using DFT
        Quasar::Dft dft(N);
        Quasar::SpectrumType dftSpectrum = dft.fft(source.toArray());

        // Aquila custom algorithm
        Quasar::AquilaFft myFft(N);
        Quasar::SpectrumType aquilaSpectrum = myFft.fft(source.toArray());

        // Ooura algorithm
        Quasar::OouraFft oouraFft(N);
        Quasar::SpectrumType oouraSpectrum = oouraFft.fft(source.toArray());

        std::cout << "  " << std::left << std::setw(7) << N <<
                     "|  " << std::setw(16) <<
                     difference(dftSpectrum, aquilaSpectrum) <<
                     "|  " << std::setw(16) <<
                     difference(dftSpectrum, oouraSpectrum) << "\n";
    }

    return 0;
}
