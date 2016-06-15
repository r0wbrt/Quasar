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
 * @file SincFilter.h
 *
 * Generates an ideal low pass filter of length 2N+1. Should be
 * multiplied by a window function to reduce ringing.
 *
 * @package Quasar
 * @version 4.0.0
 * @author Robert C. Taylor
 * @date 2016
 * @license  http://www.apache.org/licenses/LICENSE-2.0
 * @since 4.0.0
 */


#include "../source/SignalSource.h"
#include <boost/math/special_functions/sinc.hpp>
#include <cmath>

#ifndef QUASAR_SINCFILTER_H
#define QUASAR_SINCFILTER_H

namespace Quasar
{
	SignalSourceTemplateMod(DataType Sinc(DataType) = &boost::math::sinc_pi)
	class SincFilter : public SignalSourceType
	{
	public:
		SincFilter(FrequencyType SampleRate, DataType Frequency, std::size_t length) :
			SignalSourceType::SignalSource(SampleRate)
		{
			DataType B = Frequency / static_cast<DataType>(SampleRate);

			this->m_data.resize(2*length + 1);
			for(std::size_t i = 0; i < length; i++)
			{
				DataType value = 2.0*B*Sinc(M_PI*2.0*B*i);
				this->m_data[length - (i+1)] = value;
				this->m_data[(i+1) + length] = value;
			}
			this->m_data[length] = 2.0*B*Sinc(0.0);
		}
	};


}
#endif
