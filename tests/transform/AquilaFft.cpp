#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(AquilaFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Quasar::AquilaFft, 8>();
        deltaSpectrumTest<Quasar::AquilaFft, 16>();
        deltaSpectrumTest<Quasar::AquilaFft, 128>();
        deltaSpectrumTest<Quasar::AquilaFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Quasar::AquilaFft, 8>();
        constSpectrumTest<Quasar::AquilaFft, 16>();
        constSpectrumTest<Quasar::AquilaFft, 128>();
        constSpectrumTest<Quasar::AquilaFft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Quasar::AquilaFft, 8>();
        identityTest<Quasar::AquilaFft, 16>();
        identityTest<Quasar::AquilaFft, 128>();
        identityTest<Quasar::AquilaFft, 1024>();
    }
}
