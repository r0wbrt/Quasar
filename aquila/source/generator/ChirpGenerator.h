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

namespace Aquila {

class AQUILA_EXPORT ChirpGenerator: public Aquila::Generator {
public:
	ChirpGenerator(FrequencyType sampleFrequency);
	ChirpGenerator(FrequencyType sampleFrequency, FrequencyType startFrequency, FrequencyType stopFrequency);
	ChirpGenerator& setStartFrequency(FrequencyType startFrequency);
	ChirpGenerator& setStopFrequency(FrequencyType stopFrequency);

	virtual void generate(std::size_t samplesCount);
	virtual ~ChirpGenerator();
private:
	FrequencyType m_startFrequency;
	FrequencyType m_stopFrequency;
};

} /* namespace Aquila */
#endif /* CHIRPGENERATOR_H_ */
