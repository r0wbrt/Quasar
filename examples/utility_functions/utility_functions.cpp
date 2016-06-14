#include "aquila/functions.h"
#include "aquila/global.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    double value = 100.0;
    // convert a value to decibels
    std::cout << value << " is " << Quasar::dB(value) << " dB" << std::endl;
    std::cout << value << " is " << Quasar::dB(value, 0.001) << " dBm" << std::endl;
    // convert a complex number to decibels
    Quasar::ComplexType c(346.43, -125.1);
    std::cout << "Magnitude in decibels is " << Quasar::dB(c) << " dB" << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        // generate random integer from a range
        int num = Quasar::random(10, 40);
        // clamp (bound) the values between min and max
        std::cout << num << " clamped between 20 and 30 is "
                  << Quasar::clamp(20, num, 30) << std::endl;
    }

    return 0;
}
