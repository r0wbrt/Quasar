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
 * @package Quasar
 * @version 4.0.0-beta
 * @author Robert C. Taylor
 * @date 2016
 * @license  http://www.apache.org/licenses/LICENSE-2.0
 * @since 4.0.0
 */

#ifndef QUASAR_SOURCE_GENERATOR_CHIRPGENERATOR_H_
#define QUASAR_SOURCE_GENERATOR_CHIRPGENERATOR_H_

#include "Generator.h"
#include <cmath>

namespace Quasar
{


GeneratorClassTemplateOpen(DataType expFun(FieldType) = &std::cos)
class ChirpGenerator : public GeneratorType
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
			FieldType startFrequency, FieldType endFrequency) : Generator<DataType, FieldType, Container_t>::Generator(sampleFrequency), m_startFrequency(startFrequency), m_endFrequency(endFrequency){
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
	ChirpGenerator& setEndFrequency(FieldType endFrequency) {
		m_endFrequency = endFrequency;
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
		FieldType normStopFreq = this->m_endFrequency / this->m_sampleFrequency;
		FieldType normRepeatRate = this->m_sampleFrequency / this->m_frequency;
		FieldType phaseOffset =  this->m_phase * 2.0 * M_PI;
		FieldType k = (normStopFreq - normStartFreq) / normRepeatRate;


		std::size_t samplesPerPeriod = static_cast<std::size_t>(normRepeatRate);

		this->m_data.resize(samplesCount);

		for(std::size_t i = 0; i < samplesCount; i++)
		{
			std::size_t pos = i % samplesPerPeriod;
			this->m_data[i] = this->m_amplitude * expFun(phaseOffset + 2.0 * M_PI * (normStartFreq * pos + ((k / 2) * pos * pos)));
		}
	}
private:

	/*The frequency the chirp begins at.*/
	FieldType m_startFrequency;
	/*The frequency the chirp ends at.*/
	FieldType m_endFrequency;
};

/**
 * Complex exponential signal generation function.
 *
 * @param value The angle used as input to generate the output signal.
 * @return The value of the complex exponential at angle value.
 */
template<typename T>
std::complex<T> ComplexExp(T value)
{
	return std::complex<double>(std::cos(value), std::sin(value));
}

/**
 * Specialization of chirp generator for std::complex.
 */
template <typename T, template<typename ...> class Container_t = std::vector>
using ComplexChirpGenerator = ChirpGenerator<std::complex<T>, T, &ComplexExp<T>, Container_t>;

} /* namespace Aquila */
#endif /* QUASAR_SOURCE_GENERATOR_CHIRPGENERATOR_H_ */
