/**
 * @file CosineWindow.h
 *
 * Cosine window.
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

#ifndef COSINEWINDOW_H
#define COSINEWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Aquila
{
    /**
     * Cosine window.
     */
	SignalSourceTemplateMod(DataType Sin(DataType) = &std::sin)
    class CosineWindow : public SignalSourceType
    {
    public:
        /**
         * Creates Cosine window of given size.
         *
         * @param size window length
         */
        CosineWindow(std::size_t size):
            SignalSourceType::SignalSource()
        {
            this->m_data.reserve(size);
            for (std::size_t n = 0; n < size; ++n) {
                this->m_data.push_back(Sin(n * M_PI / static_cast<DataType>(size - 1)));
            }
        }
    };
}

#endif // COSINEWINDOW_H
