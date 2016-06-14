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
 * @file RaisedCosineFilter.h
 *
 * Generates a Raised Consine Shape for filtering.
 *
 * @package Quasar
 * @version 4.0.0
 * @author Robert C. Taylor
 * @date 2016
 * @license  http://www.apache.org/licenses/LICENSE-2.0
 * @since 4.0.0
 */

#ifndef QUASAR_RAISEDCOSINEFILTER_H_
#define QUASAR_RAISEDCOSINEFILTER_H_


#include "../source/SignalSource.h"
#include <boost/math/special_functions/sinc.hpp>
#include <cmath>

namespace Quasar
{

/**
 * Generates a Raised Cosine Shape for filtering.
 */
SignalSourceTemplateMod(DataType Sinc(DataType) = &boost::math::sinc_pi, DataType Cos(DataType) = &std::cos, DataType Abs(DataType) = &std::abs)
class RaisedCosineFilter : public SignalSourceType
{
public:
	/**
	 * Generates a Raised Cosine Shape for filtering of length 2*oneSideLength + 1.
	 *
	 * @author Robert C. Taylor
	 * @param sampleFrequency The symbol rate of the filter.
	 * @param oneSideLength Length of one side of the filter.
	 * @param beta Beta value that controls roll off of the Raised Cosine Filter.
	 */
	RaisedCosineFilter(FrequencyType sampleFrequency, std::size_t oneSideLength, DataType beta) :
		SignalSourceType::SignalSource(sampleFrequency)
	{
		std::size_t fullLength = 2.0 * oneSideLength + 1;
		this->m_data.resize(fullLength);
		this->m_data[oneSideLength + 1] = Sinc(0.0);

		for(std::size_t i = 0; i < oneSideLength; i++)
		{
			DataType bottomRh = 2.0 * beta * static_cast<DataType>(i) * static_cast<DataType>(sampleFrequency);
			DataType SincVal = Sinc(i * static_cast<DataType>(sampleFrequency) );
			DataType value;

			//TODO: Verify this is a good epsilon.
			if(Abs(bottomRh - 10E12) > 0.0)
			{
				value = SincVal / (1.0 - bottomRh*bottomRh);
			} else {
				//Limit as Cos(pi * x) / (1 - (2x)^2) -> +- 1/2. Taylor series may be better.
				//https://www.wolframalpha.com/input/?i=cos(pi*x)+%2F+(1+-+(2*x)%5E2)+at+x+%3D+-1%2F2
				value = SincVal * (M_PI / 4.0);
			}
			//Exploit Even Symmetry of the Filter.
			this->m_data[(i + oneSideLength) + 1] = value;
			this->m_data[(oneSideLength - i) - 1] = value;
		}
	}
};

}
#endif
