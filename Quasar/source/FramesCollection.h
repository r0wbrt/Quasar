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
 * @file FramesCollection.h
 *
 * A lightweight wrapper for a vector of Frames.
 *
 * @package Aquila
 * @version 4.0.0-beta
 * @author Zbigniew Siciarz, Robert C. Taylor
 * @date 2007-2014
 * @since 3.0.0
 */

#ifndef QUASAR_SOURCE_FRAMESCOLLECTION_H
#define QUASAR_SOURCE_FRAMESCOLLECTION_H

#include "../global.h"
#include "Frame.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>
#include "SignalSource.h"

namespace Quasar {

/**
 * A lightweight wrapper for a vector of Frames.
 *
 * This class is neccessary to perform signal division into frames,
 * which are then stored in container (currently std::vector). The frame
 * objects are stored by value as they are very light and cheap to copy.
 *
 * The reason this wrapper was created is to create some abstraction for
 * groups of frames, which can by saved or processed together. For example,
 * a spectrogram is an array of spectra calculated individually for each
 * frame. Sometimes the calculation doesn't involve the whole signal,
 * so a part of it is divided into frames, stored in a FramesCollection
 * and then processed.
 *
 * Individual frame objects can by accessed by iterating over the collection
 * using begin() and end() methods. These calls simply return iterators
 * pointing to the underlying container.
 */

SignalSourceTemplate
class FramesCollection
{
	/**
	 * Internal storage type.
	 */
	typedef std::vector<SignalSourceTemplatedType(Frame)> Container;

public:
	/**
	 * An iterator for the collection.
	 */

	typedef typename Container::iterator iterator;

	/**
	 * A const iterator for the collection.
	 */
	typedef typename Container::const_iterator const_iterator;

	/**
	 * Creates an empty frames collection.
	 */
	FramesCollection():
	m_frames(), m_samplesPerFrame(0)
	{
	}

	/**
	 * Creates a collection and creates frames from the source.
	 *
	 * @param source a reference to source object
	 * @param samplesPerFrame how many samples will each frame hold
	 * @param samplesPerOverlap how many samples are common to adjacent frames
	 */
	FramesCollection(const SignalSourceType& source,
			std::size_t samplesPerFrame,
			std::size_t samplesPerOverlap = 0):
	m_frames(), m_samplesPerFrame(0)
	{
		divideFrames(source, samplesPerFrame, samplesPerOverlap);
	}

	/**
	 * Destroys the collection, clearing the container.
	 */
	~FramesCollection()
	{
		clear();
	}

	/**
	 * Creates a collection when duration of each frame is known.
	 *
	 * @param source a reference to source object
	 * @param frameDuration frame duration in milliseconds
	 * @param overlap overlap as a fraction of frame length (0.0 - 1.0)
	 */
	static FramesCollection createFromDuration(const SignalSourceType& source,
			DataType frameDuration,
			DataType overlap = 0.0)
	{
		std::size_t samplesPerFrame = static_cast<std::size_t>(
				source.getSampleFrequency() * frameDuration / 1000.0
		);
		std::size_t samplesPerOverlap = static_cast<std::size_t>(
				samplesPerFrame * overlap
		);
		return FramesCollection(source, samplesPerFrame, samplesPerOverlap);
	}

	/**
	 * Performs the actual frame division.
	 *
	 * Frames are only "pointing" to the original source. There is no copying
	 * of sample data. Each frame can be considered as a standalone fragment
	 * of the source data.
	 *
	 * @param source a reference to source object
	 * @param samplesPerFrame how many samples will each frame hold
	 * @param samplesPerOverlap how many samples are common to adjacent frames
	 */
	void divideFrames(const SignalSourceType& source,
			std::size_t samplesPerFrame,
			std::size_t samplesPerOverlap = 0)
	{
		if (samplesPerFrame == 0)
		{
			return;
		}
		m_samplesPerFrame = samplesPerFrame;
		const std::size_t sourceSize = source.getSamplesCount();
		const std::size_t nonOverlapped = samplesPerFrame - samplesPerOverlap;
		const std::size_t framesCount = sourceSize / nonOverlapped;

		m_frames.reserve(framesCount);
		std::size_t indexBegin = 0, indexEnd = 0;
		for (std::size_t i = 0; i < framesCount; ++i)
		{
			// calculate each frame boundaries
			// when frame end exceeds source size, break out
			indexBegin = i * nonOverlapped;
			indexEnd = indexBegin + samplesPerFrame;
			if (indexEnd <= sourceSize)
			{
				m_frames.push_back(SignalSourceTemplatedType(Frame)(source, indexBegin, indexEnd));
			}
			else
			{
				break;
			}
		}
	}

	/**
	 * Deletes all contained frames and clears the collection.
	 */
	void clear()
	{
		m_frames.clear();
	}

	/**
	 * Returns number of frames in the collection.
	 *
	 * @return frames' container size
	 */
	std::size_t count() const
	{
		return m_frames.size();
	}

	/**
	 * Returns number of samples in each frame.
	 *
	 * @return frame size in samples
	 */
	std::size_t getSamplesPerFrame() const
	{
		return m_samplesPerFrame;
	}

	/**
	 * Returns nth frame in the collection.
	 *
	 * @param index index of the frame in the collection
	 * @return Frame instance
	 */
	SignalSourceTemplatedType(Frame) frame(std::size_t index) const
	{
		return m_frames[index];
	}

	/**
	 * Returns an iterator pointing to the first frame.
	 *
	 * @return iterator
	 */
	iterator begin()
	{
		return m_frames.begin();
	}

	/**
	 * Returns a const iterator pointing to the first frame.
	 *
	 * @return iterator
	 */
	const_iterator begin() const
	{
		return m_frames.begin();
	}

	/**
	 * Returns an iterator pointing one-past-last frame.
	 *
	 * @return iterator
	 */
	iterator end()
	{
		return m_frames.end();
	}

	/**
	 * Returns a const iterator pointing one-past-last frame.
	 *
	 * @return iterator
	 */
	const_iterator end() const
	{
		return m_frames.end();
	}

	/**
	 * Applies the calculation f to all frames in the collection.
	 *
	 * @param f a function whose single argument is a SignalSource
	 * @return vector of return values of f - one for each frame
	 */
	template <typename ResultType>
	std::vector<ResultType> apply(
			std::function<ResultType (const SignalSourceType&)> f) const
	{
		std::vector<ResultType> results;
		std::transform(begin(), end(), std::back_inserter(results), f);
		return results;
	}

private:
	/**
	 * Frames container.
	 */
	Container m_frames;

	/**
	 * Number of samples in each frame.
	 */
	std::size_t m_samplesPerFrame;
};}

#endif // QUASAR_SOURCE_FRAMESCOLLECTION_H
