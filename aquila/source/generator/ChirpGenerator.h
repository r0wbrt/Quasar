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
 * @file ChirpGenerator.h
 *
 * Generates a linear chirp.
 *
 * @package Aquila
 * @version 3.1.0-dev
 * @author Robert C. Taylor
 * @date 2016
 * @license  http://www.apache.org/licenses/LICENSE-2.0
 * @since 3.1.0
 */

#ifndef CHIRPGENERATOR_H_
#define CHIRPGENERATOR_H_

#include "Generator.h"
#include <cmath>

namespace Aquila
{

template <typename T>
class defExp
{
public:
	T operator()(T value)
	{
		return std::cos(value);
	}
};


template <typename DataType, typename FieldType = DataType, typename expFun = defExp<FieldType>, template<typename ...> class Container_t = std::vector>
class ChirpGenerator : public Generator<DataType, FieldType, Container_t>
{
public:
	/*
	 * Creates the chirp generator object.
	 *
	 * @param sampleFrequency The frequency at which the waveform is being
	 * sampled.
	 */
	ChirpGenerator(FieldType sampleFrequency) : Generator<DataType, FieldType, Container_t>::Generator(sampleFrequency) {
	}

	/*
	 * Creates the chirp generator object.
	 *
	 * @param sampleFrequency The frequency at which the waveform is being sampled.
	 * @param startFrequency The frequency the chirp will begin at t=0.
	 * @param stopFrequency The frequency the chirp will end at when t=1/frequency.
	 */
	ChirpGenerator(FieldType sampleFrequency,
			FieldType startFrequency, FieldType stopFrequency) : Generator<DataType, FieldType, Container_t>::Generator(sampleFrequency), m_startFrequency(startFrequency), m_stopFrequency(stopFrequency){
	}

	/*
	 * Sets the frequency the chirp begins at t=0.
	 *
	 * @param startFrequency The frequency the chirp will begin at.
	 * @return Returns the ChirpGenerator object for chaining.
	 */

	ChirpGenerator& setStartFrequency(
			FieldType startFrequency) {
		m_startFrequency = startFrequency;
		return *(this);
	}

	/*
	 * Sets the stop frequency of the chirp when t = n/frequency.
	 *
	 * @param stopFrequency The frequency the generator will stop at.
	 * @return Return the ChirpGenerator object for chaining.
	 */
	ChirpGenerator& setStopFrequency(FieldType stopFrequency) {
		m_stopFrequency = stopFrequency;
		return *(this);
	}


	/*
	 * Generates a linear chirp from start to stop frequency with
	 * time period 1/Frequency (setFrequency). setPhase sets the
	 * initial phase of the signal.
	 *
	 * @param samplesCount The number of samples to generate. A value
	 * larger then sampleFrequency /frequency will result in
	 * a periodic waveform.
	 */
	void generate(std::size_t samplesCount) {

		FieldType normStartFreq = this->m_startFrequency / this->m_sampleFrequency;
		FieldType normStopFreq = this->m_stopFrequency / this->m_sampleFrequency;
		FieldType normRepeatRate = this->m_sampleFrequency / this->m_frequency;
		FieldType phaseOffset =  this->m_phase * 2.0 * M_PI;
		FieldType k = (normStopFreq - normStartFreq) / normRepeatRate;

		expFun exp;

		std::size_t samplesPerPeriod = static_cast<std::size_t>(normRepeatRate);

		this->m_data.resize(samplesCount);

		for(std::size_t i = 0; i < samplesCount; i++)
		{
			std::size_t pos = i % samplesPerPeriod;
			this->m_data[i] = this->m_amplitude * exp(phaseOffset + 2.0 * M_PI * (normStartFreq * pos + ((k / 2) * pos * pos)));
		}
	}

	virtual ~ChirpGenerator();
private:

	FieldType m_startFrequency;
	FieldType m_stopFrequency;
};

} /* namespace Aquila */
#endif /* CHIRPGENERATOR_H_ */
