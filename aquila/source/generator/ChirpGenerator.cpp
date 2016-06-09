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
 * @file ChirpGenerator.cpp
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

#include "ChirpGenerator.h"

namespace Aquila {

/*
 * Creates the chirp generator object.
 *
 * @param sampleFrequency The frequency at which the waveform is being
 * sampled.
 */
ChirpGenerator::ChirpGenerator(FrequencyType sampleFrequency) : Generator(sampleFrequency) {
}

/*
 * Creates the chirp generator object.
 *
 * @param sampleFrequency The frequency at which the waveform is being sampled.
 * @param startFrequency The frequency the chirp will begin at t=0.
 * @param stopFrequency The frequency the chirp will end at when t=1/frequency.
 */
ChirpGenerator::ChirpGenerator(FrequencyType sampleFrequency,
		FrequencyType startFrequency, FrequencyType stopFrequency) : Generator(sampleFrequency), m_startFrequency(startFrequency), m_stopFrequency(stopFrequency){
}

/*
 * Sets the frequency the chirp begins at t=0.
 *
 * @param startFrequency The frequency the chirp will begin at.
 * @return Returns the ChirpGenerator object for chaining.
 */

ChirpGenerator& ChirpGenerator::setStartFrequency(
		FrequencyType startFrequency) {
	m_startFrequency = startFrequency;
	return *(this);
}

/*
 * Sets the stop frequency of the chirp when t = n/frequency.
 *
 * @param stopFrequency The frequency the generator will stop at.
 * @return Return the ChirpGenerator object for chaining.
 */
ChirpGenerator& ChirpGenerator::setStopFrequency(FrequencyType stopFrequency) {
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
void ChirpGenerator::generate(std::size_t samplesCount) {

	FrequencyType normStartFreq = m_startFrequency / m_sampleFrequency;
	FrequencyType normStopFreq = m_stopFrequency / m_sampleFrequency;
	FrequencyType normRepeatRate = m_sampleFrequency / m_frequency;
	FrequencyType phaseOffset =  m_phase * 2.0 * M_PI;
	FrequencyType k = (normStopFreq - normStartFreq) / normRepeatRate;

	std::size_t samplesPerPeriod = static_cast<std::size_t>(normRepeatRate);

	m_data.resize(samplesCount);

	for(std::size_t i = 0; i < samplesCount; i++)
	{
		std::size_t pos = i % samplesPerPeriod;
		m_data[i] = m_amplitude * std::sin(phaseOffset + 2.0 * M_PI * (normStartFreq * pos + ((k / 2) * pos * pos)));
	}
}



} /* namespace Aquila */
