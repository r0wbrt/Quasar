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
 * @file global.h
 *
 * Global library typedefs and constants.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 2.4.1
 */

#ifndef QUASAR_GLOBAL_H
#define QUASAR_GLOBAL_H

#include <complex>
#include <vector>


/**
 * Main library namespace.
 */
namespace Quasar
{
    /**
     * Library version in an easily comparable format.
     */
    const long VERSION_NUMBER = 0x400000;

    /**
     * Library version as a string.
     */
    const char* const VERSION_STRING = "4.0.0-beta";

    /**
     * Sample value type.
     */
    typedef double SampleType;

    /**
     * Sample frequency type.
     */
    typedef double FrequencyType;

    /**
     * Our standard complex number type, using double precision.
     */
    typedef std::complex<double> ComplexType;
}

#endif // QUASAR_GLOBAL_H
