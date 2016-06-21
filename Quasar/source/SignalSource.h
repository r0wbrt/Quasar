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
 * @file SignalSource.h
 *
 * A base signal source class.
 *
 * @package Quasar
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2016
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_SIGNALSOURCE_H
#define QUASAR_SOURCE_SIGNALSOURCE_H

#include "../global.h"
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <numeric>

namespace Quasar {

//Various template defines to reduce clutter.
#define SignalSourceClass(name) template<typename DataType = SampleType, template<typename ...> class Container_t = std::vector> class name : public SignalSource<DataType, Container_t>
#define SignalSourceTemplate template<typename DataType = SampleType, template<typename ...> class Container_t = std::vector>
#define SignalSourceTemplateMod(...) template <typename DataType = SampleType, __VA_ARGS__, template<typename ...> class Container_t = std::vector>
#define SignalSourceTemplatedType(name) name<DataType, Container_t>
#define SignalSourceType SignalSource<DataType, Container_t>

/**
 * An abstraction of any signal source.
 *
 * This is the base class for all signal sources cooperating with the
 * library, be it an array, a text file or a WAVE binary file. Most of
 * algorithms defined in the library expect a pointer or a reference
 * to SignalSource. The library ships with a few derived
 * classes for a quick start, including WaveFile, generators etc.
 *
 * Signal sources support the concept of iteration. Use
 * SignalSource::begin() and SignalSource::end() to obtain iterator objects,
 * which allow per-sample data access. The iterators work well with
 * C++ standard library algorithms, so feel free to use them instead of
 * manually looping and calling SignalSource::sample().
 */
SignalSourceTemplate
class SignalSource
{
public:
	/**
	 * The default constructor sets sample frequency to 0.
	 */
	SignalSource():
	m_data(), m_sampleFrequency(0)
	{
	}

	/**
	 * CThis overload initializes sample frequency of the source.
	 *
	 * @param sampleFrequency sample frequency in Hz
	 */
	SignalSource(FrequencyType sampleFrequency):
	m_data(), m_sampleFrequency(sampleFrequency)
	{
	}

	/**
	 * Initialize the source from data sampled at a given frequency.
	 *
	 * @param data pointer to a C-style array of samples (numeric values)
	 * @param dataLength length of the array
	 * @param sampleFrequency sample frequency in Hz
	 */
	template <typename Numeric>
	SignalSource(Numeric* data, std::size_t dataLength,
			FrequencyType sampleFrequency = 0):
	m_data(data, data + dataLength), m_sampleFrequency(sampleFrequency)
	{
	}

	/**
	 * Create the source from a vector of samples.
	 *
	 * @param data vector of samples
	 * @param sampleFrequency sample frequency in Hz
	 */
	SignalSource(const Container_t<DataType>& data,
			FrequencyType sampleFrequency = 0):
	m_data(data), m_sampleFrequency(sampleFrequency)
	{
	}

	/**
	 * Create the source from a (temporary) vector of samples.
	 *
	 * @param data vector of samples
	 * @param sampleFrequency sample frequency in Hz
	 */
	SignalSource(std::vector<SampleType>&& data,
			FrequencyType sampleFrequency = 0):
	m_data(std::move(data)), m_sampleFrequency(sampleFrequency)
	{
	}

	/**
	 * The destructor does nothing, but must be defined as virtual.
	 */
	virtual ~SignalSource() {}

	/**
	 * Returns sample frequency of the signal.
	 *
	 * @return sample frequency in Hz
	 */
	virtual FrequencyType getSampleFrequency() const
	{
		return m_sampleFrequency;
	}

	/**
	 * Sets sample frequency of the signal.
	 *
	 * @param sampleFrequency sample frequency in Hz
	 */
	virtual void setSampleFrequency(FrequencyType sampleFrequency)
	{
		m_sampleFrequency = sampleFrequency;
	}

	/**
	 * Returns number of bits per signal sample.
	 *
	 * @return sample size in bits
	 */
	virtual unsigned short getBitsPerSample() const
	{
		return 8 * sizeof(DataType);
	}

	/**
	 * Returns number of samples in the source.
	 *
	 * @return samples count
	 */
	virtual std::size_t getSamplesCount() const
	{
		return m_data.size();
	}

	/**
	 * Changes the length of the SignalSource, adding or removing samples
	 * as needed.
	 *
	 * @param length The new length of the SignalSource
	 * @param value The value new samples should be set to if the new length is
	 * greater then the current length of the signal. Defaults to 0.
	 * @return Returns the SignalSource object being modifified.
	 */
	virtual SignalSource& setSamplesCount(std::size_t length, DataType value = 0)
	{
		this->m_data.resize(length, value);
		return *(this);
	}
	/**
	 * Returns sample located at the "position" in the signal.
	 *
	 * @param position sample index in the signal
	 * @return sample value
	 */
	virtual DataType sample(std::size_t position) const
	{
		return m_data[position];
	}

	/**
	 * Returns sample data as a C-style array.
	 *
	 * Because vector guarantees to be contiguous in memory, we can
	 * return the address of the first element in the vector.
	 * It is valid only until next operation which modifies the vector.
	 *
	 * @return C-style array containing sample data
	 */
	virtual DataType* toArray()
	{
		return m_data.data();
	}

	/**
	 * Returns sample data as a C-style array.
	 *
	 * Because vector guarantees to be contiguous in memory, we can
	 * return the address of the first element in the vector.
	 * It is valid only until next operation which modifies the vector.
	 *
	 * @return C-style array containing sample data
	 */
	virtual const DataType* toArray() const
	{
		return m_data.data();
	}

	/**
	 * Returns number of samples in the source.
	 *
	 * This method is an alias to getSamplesCount() and it should not be
	 * implemented in derived classes.
	 *
	 * @return samples count
	 */
	std::size_t length() const
	{
		return getSamplesCount();
	}

	class iterator;

	/**
	 * Returns an iterator pointing to the first sample in the source.
	 *
	 * @return iterator
	 */
	iterator begin() const
	{
		return iterator(this, 0);
	}

	/**
	 * Returns an iterator pointing to the "one past last" sample.
	 *
	 * @return iterator
	 */
	iterator end() const
	{
		return iterator(this, getSamplesCount());
	}

	/**
	 * Iterator class enabling sequential data access.
	 *
	 * It is a forward iterator with a range from the first sample in the
	 * source to "one past last" sample.
	 */
	class iterator :
public std::iterator<std::forward_iterator_tag, int>
	{
	public:
		/**
		 * Creates an iterator associated with a given source.
		 *
		 * @param source pointer to a source on which the iterator will work
		 * @param i index of the sample in the source
		 */
		explicit iterator(const SignalSource<DataType, Container_t>* source =nullptr, unsigned int i = 0):
                m_source(source), idx(i)
            {
            }

            /**
             * Assigns another iterator in a memberwise fashion.
             *
             * @param other right-hand value iterator
             * @return reference to self
             */
            iterator& operator=(const iterator& other)
            {
                m_source = other.m_source;
                idx = other.idx;
                return (*this);
            }

            /**
             * Compares two iterators for equality.
             *
             * Iterators are equal only when they belong to the same source
             * and point to the same sample in the source.
             *
             * @param other right-hand value iterator
             * @return true, if the iterators are equal
             */
            bool operator==(const iterator& other) const
            {
                return m_source == other.m_source && idx == other.idx;
            }

            /**
             * Compares two iterators for inequality.
             *
             * Negates the equality operator.
             *
             * @param other right-hand value iterator
             * @return true only when the iterators are not equal
             */
            bool operator!=(const iterator& other) const
            {
                return !operator==(other);
            }

            /**
             * Moves the iterator one sample to the right (prefix version).
             *
             * @return reference to self
             */
            iterator& operator++()
            {
                ++idx;
                return (*this);
            }

            /**
             * Moves the iterator one sample to the right (postfix version).
             *
             * @return a copy of self before incrementing
             */
            iterator operator++(int)
            {
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            /**
             * Dereferences the iterator.
             *
             * @return signal sample value.
             */
            DataType operator*() const
            {
                return m_source->sample(idx);
            }

            /**
             * Returns the distance from the beginning of the source.
             *
             * @return number of samples between beginning and current position
             */
            std::size_t getPosition() const
            {
                return idx;
            }

        private:
            /**
             * Signal source - as a pointer - the iterators must be copyable.
             */
            const SignalSource<DataType, Container_t>* m_source;

            /**
             * Iterator's position in the source.
             */
            std::size_t idx;
        };

		/**
		 * Add a constant value to each sample.
		 *
		 * @param x value to add
		 * @return updated source
		 */
        SignalSource<DataType, Container_t>& operator+=(DataType x)
		{
        	std::transform(
	            std::begin(m_data),
	            std::end(m_data),
	            std::begin(m_data),
	            [x] (DataType y) { return x + y; }
	        );
	        return *this;
		}

        /**
         * Per-sample addition of other signal source.
         *
         * @param rhs source on the right-hand side of the operator
         * @return sum of two sources
         */
        SignalSource<DataType, Container_t>& operator+=(const SignalSource<DataType, Container_t>& rhs)
		{
            std::transform(
                std::begin(m_data),
                std::end(m_data),
                std::begin(rhs.m_data),
                std::begin(m_data),
                [] (DataType x, DataType y) { return x + y; }
            );
            return *this;
		}

        /**
         * Multiply each sample by a constant value.
         *
         * @param x multiplier
         * @return updated source
         */

        template <typename Numeric>
        SignalSource<DataType, Container_t>& operator*=(Numeric x)
		{
            std::transform(
                std::begin(m_data),
                std::end(m_data),
                std::begin(m_data),
                [x] (DataType y) { return x * y; }
            );
            return *this;
		}

        /**
         * Per-sample multiplication with other signal source.
         *
         * @param rhs source on the right-hand side of the operator
         * @return product of two sources
         */
        SignalSource<DataType, Container_t>& operator*=(const SignalSource<DataType, Container_t>& rhs)
		{
            std::transform(
                std::begin(m_data),
                std::end(m_data),
                std::begin(rhs.m_data),
                std::begin(m_data),
                [] (DataType x, DataType y) { return x * y; }
            );
            return *this;
		}

        /**
         * Overloads the [] operator for signal source for
         * sample access.
         *
         * @param index The signal sample to get.
         * @return Value of the sample at index.
         */
        DataType& operator[](std::size_t index)
        {
        	return this->m_data[index];
        }

        /**
		 * Overloads the [] operator for signal source for
		 * sample access.
		 *
		 * @param index The signal sample to get.
		 * @return Value of the sample at index.
		 */
        const DataType& operator[](std::size_t index) const
        {
        	return this->m_data[index];
        }

        /**
         * Signal source assignment operator.
         *
         * @param from The signal source that is being copied from.
         * @return this object after copying the values from from.
         */
        SignalSource& operator =(const SignalSource& from)
        {
        	this->m_data = from.m_data;
        	this->m_sampleFrequency = from.m_sampleFrequency;
        	return *(this);
        }
    protected:
        /**
         * Actual sample data.
         */
        Container_t<DataType> m_data;

        /**
         * Sample frequency of the data.
         */
        FrequencyType m_sampleFrequency;
    };

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(const SignalSource<DataType, Container_t> & lhs, DataType x)
{
	SignalSource<DataType, Container_t> result(lhs);
	return result += x;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(SignalSource<DataType, Container_t> && lhs, DataType x)
{
	lhs += x;
	return std::move(lhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(DataType x, const SignalSource<DataType, Container_t>& rhs)
{
	SignalSource<DataType, Container_t> result(rhs);
	return result += x;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(DataType x, SignalSource<DataType, Container_t>&& rhs)
{
	rhs += x;
	return std::move(rhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(const SignalSource<DataType, Container_t>& lhs, const SignalSource<DataType, Container_t>& rhs)
{
	SignalSource<DataType, Container_t> result(lhs);
	return result += rhs;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(SignalSource<DataType, Container_t>&& lhs, const SignalSource<DataType, Container_t>& rhs)
{
	lhs += rhs;
	return std::move(lhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator+(const SignalSource<DataType, Container_t>& lhs, SignalSource<DataType, Container_t>&& rhs)
{
	rhs += lhs;
	return std::move(rhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(const SignalSource<DataType, Container_t>& lhs, DataType x)
{
	SignalSource<DataType, Container_t> result(lhs);
	return result *= x;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(SignalSource<DataType, Container_t>&& lhs, DataType x)
{
	lhs *= x;
	return std::move(lhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(DataType x, const SignalSource<DataType, Container_t>& rhs)
{
	SignalSource<DataType, Container_t> result(rhs);
	return result *= x;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(DataType x, SignalSource<DataType, Container_t>&& rhs)
{
	rhs *= x;
	return std::move(rhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(const SignalSource<DataType, Container_t>& lhs, const SignalSource<DataType, Container_t>& rhs)
{
	SignalSource<DataType, Container_t> result(lhs);
	return result *= rhs;
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(SignalSource<DataType, Container_t>&& lhs, const SignalSource<DataType, Container_t>& rhs)
{
	lhs *= rhs;
	return std::move(lhs);
}

SignalSourceTemplate
SignalSource<DataType, Container_t> operator*(const SignalSource<DataType, Container_t>& lhs, SignalSource<DataType, Container_t>&& rhs)
{
	rhs *= lhs;
	return std::move(rhs);
}

/***************************************************************************
 *
 * Free-standing functions closely related to signals.
 *
 **************************************************************************/

/**
 * Calculates mean value of the signal.
 *
 * @param source signal source
 * @return signal mean
 */
SignalSourceTemplate
DataType mean(const SignalSource<DataType, Container_t>& source)
{
	DataType sum = std::accumulate(std::begin(source), std::end(source), 0.0);
	return sum / source.getSamplesCount();
}

/**
 * Calculates energy of the signal.
 *
 * @param source signal source
 * @return signal energy
 */
SignalSourceTemplate
DataType energy(const SignalSource<DataType, Container_t>& source)
{
	return std::accumulate(
			std::begin(source),
			std::end(source),
			0.0,
			[] (DataType acc, DataType value) {
				return acc + value * value;
			}
	);
}

/**
 * Calculates power of the signal.
 *
 * @param source signal source
 * @return signal power
 */
SignalSourceTemplate
DataType power(const SignalSource<DataType, Container_t>& source)
{
	return energy(source) / source.getSamplesCount();
}

/**
 * Calculates Euclidean (L2) norm of the signal.
 *
 * @param source signal source
 * @return norm
 */
SignalSourceTemplate
DataType norm(const SignalSource<DataType, Container_t>& source)
{
	return std::sqrt(energy(source));
}

/**
 * Calculates root mean square level of the signal.
 *
 * @param source signal source
 * @return RMS level
 */
SignalSourceTemplate
DataType rms(const SignalSource<DataType, Container_t>& source)
{
	return std::sqrt(power(source));
}

/**
 * Applies a Signal Source as an fir filter to an array of samples. Returns the summed output.
 *
 * @author Robert C. Taylor
 * @param source the SignalSource to multiply the samples by.
 * @param x the array of samples the fir filter is being applied to. Should be at least the size of the signal source.
 * @return The output of the fir filter applied to the array of samples.
 */
SignalSourceTemplate DataType ApplyFirFilter(const SignalSource<DataType, Container_t>& source, const DataType x[])
{
	return std::inner_product(source.begin(), source.end(), x, 0.0);
}
}

#endif //QUASAR_SOURCE_SIGNALSOURCE_H
