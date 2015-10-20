/**
 * @file BlackmanHarrisWindow.cpp
 *
 * Blackman-Harris window.
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

#include "BlackmanHarrisWindow.h"
#include <cmath>

namespace Aquila
{
    /**
     * Creates Blackman-Harris window of given size.
     *
     * @param size window length
     */
    BlackmanHarrisWindow::BlackmanHarrisWindow(std::size_t size):
        SignalSource()
    {
        m_data.reserve(size);
        for (std::size_t n = 0; n < size; ++n)
        {
            m_data.push_back(
                0.35875 - 0.48829 * std::cos(2.0 * M_PI * n / double(size - 1)) +
                    0.14128 * std::cos(4.0 * M_PI * n / double(size - 1)) -
                    0.01168 * std::cos(6.0 * M_PI * n / double(size - 1))
            );
        }
    }
}