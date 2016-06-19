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
 * @file GaussianWindow.h
 *
 * Gaussian (triangular) window. Based on the formula given at:
 * http://en.wikipedia.org/wiki/Window_function#Gaussian_window
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Chris Vandevelde, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_WINDOW_GAUSSIANWINDOW_H
#define QUASAR_SOURCE_WINDOW_GAUSSIANWINDOW_H

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

#endif // QUASAR_SOURCE_WINDOW_GAUSSIANWINDOW_H
