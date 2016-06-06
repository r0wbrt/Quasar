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


ChirpGenerator::ChirpGenerator(FrequencyType sampleFrequency) : Generator(sampleFrequency) {
}

ChirpGenerator::ChirpGenerator(FrequencyType sampleFrequency,
		FrequencyType startFrequency, FrequencyType stopFrequency) : Generator(sampleFrequency), m_startFrequency(startFrequency), m_stopFrequency(stopFrequency){
}

ChirpGenerator& ChirpGenerator::setStartFrequency(
		FrequencyType startFrequency) {
	m_startFrequency = startFrequency;
	return *(this);
}

ChirpGenerator& ChirpGenerator::setStopFrequency(FrequencyType stopFrequency) {
	m_stopFrequency = stopFrequency;
	return *(this);
}

void ChirpGenerator::generate(std::size_t samplesCount) {
	//TODO: Create generator function
}



} /* namespace Aquila */
