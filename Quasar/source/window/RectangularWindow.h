/**
 * @file RectangularWindow.h
 *
 * A rectangular window (equivalent to multiplication by one).
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

#ifndef RECTANGULARWINDOW_H
#define RECTANGULARWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Quasar
{
    /**
     * Rectangular window.
     */
    SignalSourceClass(RectangularWindow)
    {
    public:
        /**
         * Creates rectangular window of given size.
         *
         * @param size window length
         */
        RectangularWindow(std::size_t size):
            SignalSourceType::SignalSource()
        {
            this->m_data.assign(size, 1.0);
        }
    };
}

#endif // RECTANGULARWINDOW_H
