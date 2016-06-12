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
 * @file SquareGenerator.h
 *
 * Square wave generator.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef SQUAREGENERATOR_H
#define SQUAREGENERATOR_H

#include "Generator.h"

namespace Aquila
{
    /**
     * Square wave generator.
     */
    GeneratorClass(SquareGenerator)
    {
    public:
        /**
         * Sets duty cycle of the generated square wave.
         *
         * Duty cycle is a fraction of period in which the signal is positive.
         *
         * @param duty duty cycle (0 < duty <= 1)
         * @return the current object for fluent interface
         */
        SquareGenerator& setDuty(DataType duty)
        {
            m_duty = duty;

            return *this;
        }

        /**
         * Creates the generator object.
         *
         * @param sampleFrequency sample frequency of the signal
         */
        SquareGenerator(FrequencyType sampleFrequency):
            GeneratorType::Generator(sampleFrequency), m_duty(0.5)
        {
        }

        /**
         * Fills the buffer with generated square samples.
         *`
         * @param samplesCount how many samples to generate
         */
        void generate(std::size_t samplesCount)
        {
            this->m_data.resize(samplesCount);
            std::size_t samplesPerPeriod = static_cast<std::size_t>(
                this->m_sampleFrequency / static_cast<FieldType>(this->m_frequency));
            std::size_t positiveLength = static_cast<std::size_t>(m_duty *
                                                                  samplesPerPeriod);

            for (std::size_t i = 0; i < samplesCount; ++i)
            {
                std::size_t t = i % samplesPerPeriod;
                this->m_data[i] = this->m_amplitude * (t < positiveLength ? 1 : -1);
            }
        }

    private:
        /**
         * Duty cycle, default = 0.5.
         */
        FieldType m_duty;
    };
}

#endif // SQUAREGENERATOR_H
