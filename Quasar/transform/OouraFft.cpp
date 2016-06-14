/*
 *   Copyright 2016 Robert C. Taylor
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * @file OouraFft.cpp
 *
 * A wrapper for the FFT algorithm found in Ooura mathematical packages.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>

namespace Quasar
{
    /**
     * Initializes the transform for a given input length.
     *
     * Prepares the work area for Ooura's algorithm.
     *
     * @param length input signal size (usually a power of 2)
     */
    OouraFft::OouraFft(std::size_t length):
        Fft(length),
        // according to the description: "length of ip >= 2+sqrt(n)"
        ip(new int[static_cast<std::size_t>(2 + std::sqrt(static_cast<double>(N)))]),
        w(new double[N / 2])
    {
        ip[0] = 0;
    }

    /**
     * Destroys the transform object and cleans up working area.
     */
    OouraFft::~OouraFft()
    {
        delete [] w;
        delete [] ip;
    }

    /**
     * Applies the transformation to the signal.
     *
     * @param x input signal
     * @return calculated spectrum
     */
    SpectrumType OouraFft::fft(const SampleType x[])
    {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
            "complex<double> has the same memory layout as two consecutive doubles"
        );
        // create a temporary storage array and copy input to even elements
        // of the array (real values), leaving imaginary components at 0
        double* a = new double[2 * N];
        for (std::size_t i = 0; i < N; ++i)
        {
            a[2 * i] = x[i];
            a[2 * i + 1] = 0.0;
        }

        // let's call the C function from Ooura's package
        cdft(2*N, -1, a, ip, w);

        // convert the array back to complex values and return as vector
        ComplexType* tmpPtr = reinterpret_cast<ComplexType*>(a);
        SpectrumType spectrum(tmpPtr, tmpPtr + N);
        delete [] a;

        return spectrum;
    }

    /**
     * Applies the transform to a complex signal in place.
     * @author Robert C. Taylor
     * @param spectrum input signal to be transformed.
     */
    void OouraFft::fftComplexInPlace(SpectrumType& spectrum)
    {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
            "complex<double> has the same memory layout as two consecutive doubles"
        );

        double* a = reinterpret_cast<double*>(spectrum.data());

        // let's call the C function from Ooura's package
        cdft(2*N, -1, a, ip, w);
    }

    /**
     * Performs a transform to a complex signal.
     * @author Robert C. Taylor
     * @param spectrum input signal to be transformed.
     * @return the output signal.
     */
    SpectrumType OouraFft::fft(SpectrumType spectrum)
    {
    	SpectrumType buffer(spectrum);
    	fftComplexInPlace(buffer);
    	return buffer;
    }

    /**
     * Applies the inverse transform to the spectrum. No Scaling is performed on the output.
     *
     * @param spectrum input spectrum
     * @author Robert C. Taylor
     */
    void OouraFft::ifftComplexInPlace(SpectrumType& spectrum)
    {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
                "complex<double> has the same memory layout as two consecutive doubles"
        );
        // interpret the vector as consecutive pairs of doubles (re,im)
        double* a = reinterpret_cast<double*>(spectrum.data());

        // Ooura's function
        cdft(2*N, 1, a, ip, w);
    }

    /**
     * Applies the inverse transform to the spectrum.
     *
     * @param spectrum input spectrum
     * @param x output signal
     */
    void OouraFft::ifft(SpectrumType spectrum, double x[])
    {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
                "complex<double> has the same memory layout as two consecutive doubles"
        );
        // interpret the vector as consecutive pairs of doubles (re,im)
        // and copy to input/output array
        double* tmpPtr = reinterpret_cast<double*>(&spectrum[0]);
        double* a = new double[2 * N];
        std::copy(tmpPtr, tmpPtr + 2 * N, a);

        // Ooura's function
        cdft(2*N, 1, a, ip, w);

        // copy the data to the double array and scale it
        for (std::size_t i = 0; i < N; ++i)
        {
            x[i] = a[2 * i] / static_cast<double>(N);
        }
        delete [] a;
    }
}
