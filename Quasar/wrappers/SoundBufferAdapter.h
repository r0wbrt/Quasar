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
 * @file SoundBufferAdapter.h
 *
 * A wrapper around SignalSource to use as a sound buffer in SFML.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef SOUNDBUFFERADAPTER_H
#define SOUNDBUFFERADAPTER_H

#include "../global.h"
#include "../source/SignalSource.h"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <algorithm>


namespace Quasar
{


    /**
     * A wrapper around SignalSource to use as a sound buffer in SFML.
     */
    SignalSourceTemplate
    class SoundBufferAdapter : public sf::SoundBuffer
    {
    public:
        /**
         * Creates the buffer with no initial data.
         */
        SoundBufferAdapter():
        sf::SoundBuffer::SoundBuffer()
        {
        }

        /**
         * Copy constructor.
         *
         * @param other buffer instance to copy from
         */
        SoundBufferAdapter(const SoundBufferAdapter &other):
		sf::SoundBuffer::SoundBuffer(other)
        {
        }

        /**
         * Creates the buffer with initial data provided by signal source.
         *
         * @param source signal source
         */
        SoundBufferAdapter(const SignalSourceType &source):
				sf::SoundBuffer::SoundBuffer()
        {
            loadFromSignalSource(source);
        }

        /**
         * Destructor - does nothing by itself.
         *
         * Relies on virtual call to the destructor of the parent class.
         */
        ~SoundBufferAdapter()
        {
        }

        /**
         * Loads sound data from an instance of SignalSource-subclass.
         *
         * Data read from source are converted to SFML-compatible sample array
         * and loaded into the buffer.
         *
         * Name capitalized for consistency with SFML coding style.
         *
         * @todo get rid of copying data around, let's come up with some better way
         *
         * @param source signal source
         * @return true if successfully loaded
         */
        bool loadFromSignalSource(const SignalSourceType &source)
        {
            sf::Int16* samples = new sf::Int16[source.getSamplesCount()];
            std::copy(source.begin(), source.end(), samples);
            bool result = this->loadFromSamples(samples,
                                         source.getSamplesCount(),
                                         1,
                                         static_cast<unsigned int>(source.getSampleFrequency()));
            delete [] samples;

            return result;
        }
    };
}

#endif // SOUNDBUFFERADAPTER_H
