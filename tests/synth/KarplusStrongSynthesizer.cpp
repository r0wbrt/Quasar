#include "aquila/synth/KarplusStrongSynthesizer.h"
#include "UnitTest++/UnitTest++.h"


SUITE(KarplusStrongSynthesizer)
{
    TEST(PlayNote)
    {
        Quasar::KarplusStrongSynthesizer synthesizer(44100);
        synthesizer.playNote("A4", 100);
    }

    TEST(PlayUnknownNote)
    {
        Quasar::KarplusStrongSynthesizer synthesizer(44100);
        synthesizer.playNote("XX", 100);
    }
}
