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
 * @file WhiteNoiseGenerator.h
 *
 * White noise generator.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_GENERATOR_WHITENOISEGENERATOR_H
#define QUASAR_SOURCE_GENERATOR_WHITENOISEGENERATOR_H

#include "Generator.h"
#include "../../functions.h"

namespace Quasar
{
    /**
     * White noise generator.
     */
	GeneratorClassTemplateOpen(DataType RandomData() = &randomDouble)
    class WhiteNoiseGenerator : public GeneratorType
    {
    public:
        /**
         * Creates the generator object.
         *
         * @param sampleFrequency sample frequency of the signal
         */
        WhiteNoiseGenerator(FrequencyType sampleFrequency):
            GeneratorType::Generator(sampleFrequency)
        {
        }

        /**
         * Fills the buffer with generated white noise samples.
         *
         * @param samplesCount how many samples to generate
         */
        void generate(std::size_t samplesCount)
        {
            this->m_data.resize(samplesCount);
            for (std::size_t i = 0; i < samplesCount; ++i)
            {
                this->m_data[i] = this->m_amplitude * (RandomData() - 0.5);
            }
        }
    };
}

#endif // QUASAR_SOURCE_GENERATOR_WHITENOISEGENERATOR_H
