/**
 * @file WelchWindow.h
 *
 * Welch window.
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

#ifndef WELCHWINDOW_H
#define WELCHWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Quasar
{
    /**
     * Welch window.
     */
    SignalSourceClass(WelchWindow)
    {
    public:
        /**
         * Creates Welch window of given size.
         *
         * @param size window length
         */
        WelchWindow(std::size_t size):
            SignalSourceType::SignalSource()
        {

            const DataType lhalf = (static_cast<DataType>(size) - 1.0) / 2.0; // L / 2
            this->m_data.reserve(size);
            for (std::size_t n = 0; n < size; ++n)
            {
                DataType v = ((DataType)n - lhalf) / lhalf;
                this->m_data.push_back(1 - (v * v));
            }
        }
    };
}

#endif // WELCHWINDOW_H
