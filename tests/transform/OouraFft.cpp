#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(OouraFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Quasar::OouraFft, 8>();
        deltaSpectrumTest<Quasar::OouraFft, 16>();
        deltaSpectrumTest<Quasar::OouraFft, 128>();
        deltaSpectrumTest<Quasar::OouraFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Quasar::OouraFft, 8>();
        constSpectrumTest<Quasar::OouraFft, 16>();
        constSpectrumTest<Quasar::OouraFft, 128>();
        constSpectrumTest<Quasar::OouraFft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Quasar::OouraFft, 8>();
        deltaInverseTest<Quasar::OouraFft, 16>();
        deltaInverseTest<Quasar::OouraFft, 128>();
        deltaInverseTest<Quasar::OouraFft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Quasar::OouraFft, 8>();
        constInverseTest<Quasar::OouraFft, 16>();
        constInverseTest<Quasar::OouraFft, 128>();
        constInverseTest<Quasar::OouraFft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Quasar::OouraFft, 8>();
        identityTest<Quasar::OouraFft, 16>();
        identityTest<Quasar::OouraFft, 128>();
        identityTest<Quasar::OouraFft, 1024>();
    }
}
