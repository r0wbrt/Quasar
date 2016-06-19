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
 * @file RawPcmFile.h
 *
 * Reading raw PCM binary data from file.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_RAWPCMFILE_H
#define QUASAR_SOURCE_RAWPCMFILE_H

#include "../global.h"
#include "SignalSource.h"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <string>

namespace Quasar
{
    /**
     * A class to read raw PCM binary data from file.

     * No headers are allowed in the file.
     *
     * Any numeric type will be converted on the fly to SampleType. Sample
     * rate must be known prior to opening the file as the constructor expects
     * sample frequency as its second argument.
     */

    SignalSourceClass(RawPcmFile)
    {
    public:
        /**
         * Creates the data source.
         *
         * @param filename full path to data file
         * @param sampleFrequency sample frequency of the data in file
         */
        RawPcmFile(std::string filename, FrequencyType sampleFrequency):
            SignalSourceType::SignalSource(sampleFrequency)
        {
            std::fstream fs;
            fs.open(filename.c_str(), std::ios::in | std::ios::binary);
            // get file size by seeking to the end and telling current position
            fs.seekg(0, std::ios::end);
            std::streamsize fileSize = fs.tellg();
            // seek back to the beginning so read() can access all content
            fs.seekg(0, std::ios::beg);
            std::size_t samplesCount = fileSize / sizeof(Numeric);
            // read raw data into a temporary buffer
            DataType* buffer = new DataType[samplesCount];
            fs.read((char*)buffer, fileSize);
            // copy and implicit conversion to SampleType
            this->m_data.assign(buffer, buffer + samplesCount);
            delete [] buffer;
            fs.close();
        }

        /**
         * Saves the given signal source as a raw PCM file.
         *
         * @param source source of the data to save
         * @param filename destination file
         */
        static void save(const SignalSourceType& source, const std::string& filename)
        {
            std::fstream fs;
            fs.open(filename.c_str(), std::ios::out | std::ios::binary);
            std::size_t samplesCount = source.getSamplesCount();
            DataType* buffer = new DataType[samplesCount];
            // copy and convert from SampleType to target type
            std::copy(std::begin(source), std::end(source), buffer);
            fs.write((char*)buffer, samplesCount * sizeof(DataType));
            delete [] buffer;
            fs.close();
        }
    };
}

#endif // QUASAR_SOURCE_RAWPCMFILE_H
