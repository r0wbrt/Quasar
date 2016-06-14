/**
 * @file HammingWindow.h
 *
 * Hamming window.
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

#ifndef HAMMINGWINDOW_H
#define HAMMINGWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Quasar
{
    /**
     * Hamming window.
     */
	SignalSourceTemplateMod(DataType Cos(DataType) = &std::cos)
    class HammingWindow : public SignalSourceType
    {
    public:
        /**
         * Creates Hamming window of given size.
         *
         * @param size window length
         */
        HammingWindow(std::size_t size):
            SignalSourceType::SignalSource()
        {
            this->m_data.reserve(size);
            for (std::size_t n = 0; n < size; ++n)
            {
                this->m_data.push_back(
                    0.53836 - 0.46164 * Cos(2.0 * M_PI * n / static_cast<DataType>(size - 1))
                );
            }
        }
    };
}

#endif // HAMMINGWINDOW_H
