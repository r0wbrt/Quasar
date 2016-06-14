/**
 * @file PlainTextFile.h
 *
 * Reading samples from a plain text file.
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

#ifndef PLAINTEXTFILE_H
#define PLAINTEXTFILE_H

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

#endif // PLAINTEXTFILE_H
