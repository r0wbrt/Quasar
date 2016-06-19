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
 * @file PlainTextFile.h
 *
 * Reading samples from a plain text file.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_PLAINTEXTFILE_H
#define QUASAR_SOURCE_PLAINTEXTFILE_H

#include "../global.h"
#include "SignalSource.h"
#include <string>

namespace Quasar
{
    /**
     * Plain text file, where each sample is in new line.
     *
     * No headers are allowed in the file, only a simple list of numbers
     * will work at the moment.
     *
     * Any numeric type will be converted on the fly to SampleType. Sample
     * rate must be known prior to opening the file as the constructor expects
     * sample frequency as its second argument.
     */
    SignalSourceClass(PlainTextFile)
    {
    public:
        /**
         * Creates the data source.
         *
         * @param filename full path to .txt file
         * @param sampleFrequency sample frequency of the data in file
         */
        PlainTextFile(std::string filename,
                                     FrequencyType sampleFrequency):
            SignalSourceType::SignalSource(sampleFrequency)
        {
            std::fstream fs;
            fs.open(filename.c_str(), std::ios::in);
            std::copy(std::istream_iterator<DataType>(fs),
                      std::istream_iterator<DataType>(),
                      std::back_inserter(this->m_data));
            fs.close();
        }

        /**
         * Saves the given signal source as a plain text file.
         *
         * @param source source of the data to save
         * @param filename destination file
         */
        void PlainTextFile::save(const SignalSourceType& source,
                                 const std::string& filename)
        {
            std::fstream fs;
            fs.open(filename.c_str(), std::ios::out);
            std::copy(std::begin(source),
                      std::end(source),
                      std::ostream_iterator<DataType>(fs, "\n"));
            fs.close();
        }
    }
    };
}

#endif // QUASAR_SOURCE_PLAINTEXTFILE_H
