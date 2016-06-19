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
 * @file Fft.h
 *
 * An interface for FFT calculation classes.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_TRANSFORM_FFT_H
#define QUASAR_TRANSFORM_FFT_H

#include "../global.h"
#include "../source/SignalSource.h"
#include <cstddef>

namespace Quasar
{
    /**
     * An interface for FFT calculation classes.
     *
     * The abstract interface for FFT algorithm allows switching between
     * implementations at runtime, or selecting a most effective implementation
     * for the current platform.
     *
     * The FFT objects are not intended to be copied.
     *
     * Some of FFT implementations prepare a "plan" or create a coefficient
     * cache only once, and then run the transform on multiple sets of data.
     * Aquila expresses this approach by defining a meaningful constructor
     * for the base FFT interface. A derived class should calculate the
     * plan once - in the constructor (based on FFT length). Later calls
     * to fft() / ifft() should reuse the already created plan/cache.
     */
	SignalSourceTemplate
    class Fft
    {
    public:
        /**
         * Initializes the transform for a given input length.
         *
         * @param length input signal size (usually a power of 2)
         */
        Fft(std::size_t length): N(length)
        {
        }

        /**
         * Destroys the transform object - does nothing.
         *
         * As the derived classes may perform some deinitialization in
         * their destructors, it must be declared as virtual.
         */
        virtual ~Fft()
        {
        }

        /**
         * Applies the forward FFT transform to the signal source.
         *
         * @param x input signal
         */
        virtual void fft(SignalSourceType& signal) = 0;

        /**
         * Applies the inverse FFT transform to the signal source.
         *
         * @param spectrum input spectrum
         */
        virtual void ifft(SignalSourceType& signal) = 0;


    protected:
        /**
         * Signal and spectrum length.
         */
        std::size_t N;

    private:
        Fft( const Fft& );
        const Fft& operator=( const Fft& );
    };
}

#endif // QUASAR_TRANSFORM_FFT_H
