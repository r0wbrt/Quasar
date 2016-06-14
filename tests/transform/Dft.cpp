#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/Dft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(Dft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Quasar::Dft, 8>();
        deltaSpectrumTest<Quasar::Dft, 16>();
        deltaSpectrumTest<Quasar::Dft, 128>();
        deltaSpectrumTest<Quasar::Dft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Quasar::Dft, 8>();
        constSpectrumTest<Quasar::Dft, 16>();
        constSpectrumTest<Quasar::Dft, 128>();
        constSpectrumTest<Quasar::Dft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Quasar::Dft, 8>();
        deltaInverseTest<Quasar::Dft, 16>();
        deltaInverseTest<Quasar::Dft, 128>();
        deltaInverseTest<Quasar::Dft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Quasar::Dft, 8>();
        constInverseTest<Quasar::Dft, 16>();
        constInverseTest<Quasar::Dft, 128>();
        constInverseTest<Quasar::Dft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Quasar::Dft, 8>();
        identityTest<Quasar::Dft, 16>();
        identityTest<Quasar::Dft, 128>();
        identityTest<Quasar::Dft, 1024>();
    }
}
