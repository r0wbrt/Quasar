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

#ifndef QUASAR_EXPERIMENTAL_FIXEDTYPE_H
#define QUASAR_EXPERIMENTAL_FIXEDTYPE_H

namespace Quasar
{

template <typename StoreType>
class FixedType
{
public:
	FixedType()
	{
		m_value = 0;
		m_fractionalBits = sizeof(StoreType)*4;
	}

	FixedType(StoreType value)
	{
		m_value = value << m_fractionalBits;
	}

	FixedType(double value)
	{
		m_value = static_cast<StoreType>(value * std::pow(2, m_fractionalBits));
	}


private:
	StoreType m_value;
	std::size_t m_fractionalBits;
};

}


#endif
