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
 * @file TriangleGenerator.h
 *
 * Triangle (and sawtooth) wave generator.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_GENERATOR_TRIANGLEGENERATOR_H
#define QUASAR_SOURCE_GENERATOR_TRIANGLEGENERATOR_H

#include "Generator.h"
#include <cmath>

namespace Quasar
{
    /**
     * Triangle (and sawtooth) wave generator.
     */
    GeneratorClass(TriangleGenerator)
    {
    public:
        /**
         * Creates the generator object.
         *
         * @param sampleFrequency sample frequency of the signal
         */
        TriangleGenerator(FrequencyType sampleFrequency):
            GeneratorType::Generator(sampleFrequency), m_width(1.0)
        {
        }

        /**
         * Fills the buffer with generated triangle wave samples.
         *
         * The default behaviour is to generate a sawtooth wave. To change that
         * to a triangle wave, call setWidth() with some value between 0 and 1.
         *
         * @param samplesCount how many samples to generate
         */
        void generate(std::size_t samplesCount)
        {
            this->m_data.resize(samplesCount);

            FieldType dt = 1.0 / this->m_sampleFrequency;
            FieldType period = 1.0 / this->m_frequency;
            FieldType risingLength = m_width * period;
            FieldType fallingLength = period - risingLength;

            FieldType risingIncrement =
                (risingLength != 0) ? (2.0 * this->m_amplitude / risingLength) : 0;

            FieldType fallingDecrement =
                (fallingLength != 0) ? (2.0 * this->m_amplitude / fallingLength) : 0;

            FieldType t = 0;
            for (std::size_t i = 0; i < samplesCount; ++i)
            {
                if (t > period)
                {
                    t -= period;
                }
                if (t < risingLength)
                {
                    this->m_data[i] = -this->m_amplitude + t * risingIncrement;
                }
                else
                {
                    this->m_data[i] = this->m_amplitude - (t - risingLength) * fallingDecrement;
                }
                t += dt;
            }
        }
        /**
         * Sets slope width of the generated triangle wave.
         *
         * Slope width is a fraction of period in which signal is rising.
         *
         * @param width slope width (0 < width <= 1)
         * @return the current object for fluent interface
         */
        TriangleGenerator& setWidth(FieldType width)
        {
            m_width = width;

            return *this;
        }

    private:
        /**
         * Slope width, default = 1.0 (generates sawtooth wave).
         */
        FieldType m_width;
    };
}

#endif // QUASAR_SOURCE_GENERATOR_TRIANGLEGENERATOR_H
