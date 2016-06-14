#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "aquila/source/generator/PinkNoiseGenerator.h"
#include "aquila/tools/TextPlot.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    // seed the random number generator
    std::srand(std::time(0));

    Quasar::WhiteNoiseGenerator white(1000);
    white.setAmplitude(1024).generate(64);
    Quasar::TextPlot plot("White noise");
    plot.plot(white);

    Quasar::PinkNoiseGenerator pink(1000);
    pink.setAmplitude(1024).generate(64);
    plot.setTitle("Pink noise");
    plot.plot(pink);

    return 0;
}
