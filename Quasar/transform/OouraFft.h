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
 * @file OouraFft.h
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

#ifndef OOURAFFT_H
#define OOURAFFT_H

#include "Fft.h"

extern "C" {
    void cdft(int, int, double *, int *, double *);
    void rdft(int, int, double *, int *, double *);
}

namespace Quasar
{
    /**
     * A wrapper for the FFT algorithm found in Ooura mathematical packages.
     */
    class AQUILA_EXPORT OouraFft : public Fft
    {
    public:
        OouraFft(std::size_t length);
        ~OouraFft();

        virtual SpectrumType fft(const SampleType x[]);
        virtual void ifft(SpectrumType spectrum, double x[]);
        virtual void fftComplexInPlace(SpectrumType& specrum);
        virtual void ifftComplexInPlace(SpectrumType& spectrum);
        virtual SpectrumType fft(SpectrumType spectrum);

    private:
        /**
         * Work area for bit reversal.
         */
        int* ip;

        /**
         * Cos/sin table.
         */
        double* w;
    };
}

#endif // OOURAFFT_H
