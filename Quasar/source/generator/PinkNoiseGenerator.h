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
 * @file PinkNoiseGenerator.h
 *
 * Pink noise generator.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_GENERATOR_PINKNOISEGENERATOR_H
#define QUASAR_SOURCE_GENERATOR_PINKNOISEGENERATOR_H

#include "Generator.h"
#include "../../functions.h"

namespace Quasar
{
	/** Number of samples noise samples to use in the Voss algorithm */
	#define PinkNoiseGeneratorwhiteSamplesNum 20
    /**
     * Pink noise generator using Voss algorithm.
     */
	GeneratorClassTemplateOpen(DataType RandomData() = &randomDouble)
    class PinkNoiseGenerator : public GeneratorType
    {
    public:
        /**
         * Creates the generator object.
         *
         * @param sampleFrequency sample frequency of the signal
         */
        PinkNoiseGenerator(FrequencyType sampleFrequency):
            GeneratorType::Generator(sampleFrequency), key(0), maxKey(0xFFFF)
        {
        }

        /**
         * Fills the buffer with generated pink noise samples.
         *
         * @param samplesCount how many samples to generate
         */
        void generate(std::size_t samplesCount)
        {
            this->m_data.resize(samplesCount);

            // Voss algorithm initialization
            maxKey = 0xFFFF;
            key = 0;
            for (std::size_t i = 0; i < PinkNoiseGeneratorwhiteSamplesNum; ++i)
            {
                whiteSamples[i] = RandomData() - 0.5;
            }

            for (std::size_t i = 0; i < samplesCount; ++i)
            {
                this->m_data[i] = this->m_amplitude * pinkSample();
            }
        }

    private:

        /**
         * Generates a single pink noise sample using Voss algorithm.
         *
         * @return pink noise sample
         */
        DataType pinkSample()
        {
            int lastKey = key;
            DataType sum = 0;

            key++;
            if (key > maxKey)
                key = 0;

            int diff = lastKey ^ key;
            for (std::size_t i = 0; i < PinkNoiseGeneratorwhiteSamplesNum; ++i)
            {
                if (diff & (1 << i))
                    whiteSamples[i] = RandomData() - 0.5;
                sum += whiteSamples[i];
            }

            return sum / static_cast<FieldType>(PinkNoiseGeneratorwhiteSamplesNum);
        }



        /**
         * An internal buffer for white noise samples.
         */
        DataType whiteSamples[PinkNoiseGeneratorwhiteSamplesNum];

        /**
         * A key marking which of the white noise samples should change.
         */
        int key;

        /**
         * Maximum key value.
         */
        int maxKey;
    };
}

#endif // QUASAR_SOURCE_GENERATOR_PINKNOISEGENERATOR_H
