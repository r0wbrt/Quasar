/**
 * @file GaussianWindow.h
 *
 * Gaussian (triangular) window. Based on the formula given at:
 * http://en.wikipedia.org/wiki/Window_function#Gaussian_window
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Chris Vandevelde
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef GAUSSIANWINDOW_H
#define GAUSSIANWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Quasar
{
    /**
     * Creates Gaussian window of given size, with optional sigma parameter.
     */
	SignalSourceTemplateMod(DataType Pow(DataType, DataType) = &std::pow, DataType Exp(DataType) = &std::exp)
    class GaussianWindow : public SignalSourceType
    {
    public:
        /**
         * Creates Gaussian window of given size, with optional sigma parameter.
         *
         * @param size window length
         * @param sigma standard deviation
         */
        GaussianWindow(std::size_t size, DataType sigma = 0.5):
            SignalSourceType::SignalSource()
        {
            this->m_data.reserve(size);
            for (std::size_t n = 0; n < size; ++n)
            {
                this->m_data.push_back(
                    Exp((-0.5) * Pow((n - (size - 1.0) / 2.0)/(sigma * (size - 1.0) / 2.0), 2.0))
                );
            }
        }
    };
}

#endif // GAUSSIANWINDOW_H
