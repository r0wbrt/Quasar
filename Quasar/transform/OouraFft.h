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
     * A wrapper for the complex FFT algorithm found in Ooura mathematical packages.
     */
	template<template<typename ...> class Container_t = std::vector>
    class OouraFftComplex : public Fft<std::complex<double>, Container_t>
    {
    public:
    	/**
    	    * Initializes the transform for a given input length.
    	    *
    	    * Prepares the work area for Ooura's algorithm.
    	    *
    	    * @param length input signal size (usually a power of 2)
    	    */
    	   OouraFftComplex(std::size_t length):
    	       Fft<std::complex<double>, Container_t>::Fft(length),
    	       // according to the description: "length of ip >= 2+sqrt(n)"
    	       ip(new int[static_cast<std::size_t>(2 + std::sqrt(static_cast<double>(this->N)))]),
    	       w(new double[this->N / 2])
    	   {
    	       ip[0] = 0;
    	   }

    	   /**
    	    * Destroys the transform object and cleans up working area.
    	    */
    	   ~OouraFftComplex()
    	   {
    	       delete [] w;
    	       delete [] ip;
    	   }

        /**
         * Applies the inverse transform to the spectrum. No Scaling is performed on the output.
         *
         * @param spectrum input spectrum
         * @author Robert C. Taylor
         */
        virtual void ifft(SignalSource<std::complex<double>, Container_t>& spectrum)
        {
        	fftInternal(spectrum, -1);
        }

        /**
		* Applies the transform to a complex signal in place.
		* @author Robert C. Taylor
		* @param spectrum input signal to be transformed.
		*/
	   virtual void fft(SignalSource<std::complex<double>, Container_t>& spectrum)
	   {
		   fftInternal(spectrum, 1);
	   }



    private:

	   void fftInternal(SignalSource<std::complex<double>, Container_t>& spectrum, int direction)
	   {
           static_assert(
                sizeof(std::complex<double>[2]) == sizeof(double[4]),
                    "complex<double> has the same memory layout as two consecutive doubles"
            );

            // Ooura's function
            cdft(2*this->N, direction, reinterpret_cast<double*>(spectrum.toArray()), ip, w);

            if(direction == -1)
            {
				spectrum *= 1.0 / static_cast<double>(this->N);

            }

	   }

        /**
         * Work area for bit reversal.
         */
        int* ip;

        /**
         * Cos/sin table.
         */
        double* w;
    };


    /**
     * A wrapper for the real FFT algorithm found in Ooura mathematical packages.
     * Does n/2 decimation on the real signal.
     */
	template<template<typename ...> class Container_t = std::vector>
    class OouraFftReal : public Fft<double, Container_t>
    {
    public:

    	/**
		* Initializes the transform for a given input length.
		*
		* Prepares the work area for Ooura's algorithm.
		*
		* @param length input signal size (usually a power of 2)
		*/
	   OouraFftReal(std::size_t length):
		   Fft<double, Container_t>::Fft(length),
		   // according to the description: "length of ip >= 2+sqrt(n/2)"
		   ip(new int[static_cast<std::size_t>(2 + std::sqrt(static_cast<double>(this->N / 2)))]),
		   w(new double[this->N / 2])
	   {
		   ip[0] = 0;
	   }

	   /**
		* Destroys the transform object and cleans up working area.
		*/
	   ~OouraFftReal()
	   {
		   delete [] w;
		   delete [] ip;
	   }

        /**
         * Applies the inverse transform to a real signal in place. Decimates by 2.
         *
         * @param spectrum input spectrum
         * @author Robert C. Taylor
         */
        virtual void ifft(SignalSource<double, Container_t>& spectrum)
        {
        	fftInternal(spectrum, -1);
        }

        /**
		* Applies the transform to a complex signal in place.
		* @author Robert C. Taylor
		* @param spectrum input signal to be transformed.
		*/
	   virtual void fft(SignalSource<double, Container_t>& spectrum)
	   {
		   fftInternal(spectrum, 1);
	   }

    private:

	   void fftInternal(SignalSource<double, Container_t>& spectrum, int direction)
	   {

           rdft(this->N, direction, reinterpret_cast<double*>(spectrum.toArray()), ip, w);

           if(direction==-1)
           {
			   spectrum *= 2.0 / static_cast<double>(this->N);
           }
	   }

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
