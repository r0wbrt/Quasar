#include "aquila/source/window/BarlettWindow.h"
#include "aquila/source/window/BlackmanWindow.h"
#include "aquila/source/window/FlattopWindow.h"
#include "aquila/source/window/HammingWindow.h"
#include "aquila/source/window/HannWindow.h"
#include "aquila/source/window/RectangularWindow.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    const std::size_t LENGTH = 65;
    Quasar::TextPlot plot;

    Quasar::BarlettWindow barlett(LENGTH);
    plot.setTitle("Barlett");
    plot.plot(barlett);

    Quasar::BlackmanWindow blackman(LENGTH);
    plot.setTitle("Blackman");
    plot.plot(blackman);

    Quasar::FlattopWindow flattop(LENGTH);
    plot.setTitle("Flattop");
    plot.plot(flattop);

    Quasar::HammingWindow hamming(LENGTH);
    plot.setTitle("Hamming");
    plot.plot(hamming);

    Quasar::HannWindow hann(LENGTH);
    plot.setTitle("Hann");
    plot.plot(hann);

    Quasar::RectangularWindow rect(LENGTH);
    plot.setTitle("Rectangular");
    plot.plot(rect);

    return 0;
}
