/**
 * @file functions.h
 *
 * Miscellaneous utility functions.
 *
 * @package Quasar
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "global.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>

namespace Quasar
{
    /**
     * Converts the value to decibels (assuming reference value equal to 1).
     *
     * @param value input value
     * @return value in dB
     */
    template<typename Numeric>
    inline Numeric dB(Numeric value)
    {
        return 20.0 * std::log10(value);
    }

    /**
     * Convert the magnitude of a complex number to decibels.
     *
     * @param value input value (complex number)
     * @return magnitude in dB
     */
    template<template <typename ...> typename complex, typename Numeric>
    inline Numeric dB(complex<Numeric> value)
    {
        return dB(std::abs(value));
    }

    /**
     * Converts the value to decibels, relative to the reference value.
     *
     * @param value input value
     * @param refValue reference value
     * @return value in dB, relative to reference value
     */
    template<typename Numeric>
     Numeric dB(Numeric value, Numeric refValue)
    {
        return 20.0 * std::log10(value / refValue);
    }

    /**
     * Clamps (limits) the value inside a range.
     *
     * @param min lower limit
     * @param value numver to clamp
     * @param max upper limit
     * @return bounded value
     */
    template<typename Numeric>
    Numeric clamp(Numeric min, Numeric value, Numeric max)
    {
        return std::max(min, std::min(value, max));
    }

    /**
     * Returns a pseudorandom value from a range.
     *
     * @param from lower limit
     * @param to upper limit
     * @return random number
     */
    inline int random(int from, int to)
    {
        return std::rand() % (to - from) + from;
    }

    /**
     * Returns a pseudorandom double number from 0 to 1.
     */
    inline double randomDouble()
    {
        return std::rand() / static_cast<double>(RAND_MAX);
    }

    /**
     * Checks if n is an exact power of 2.
     */
    template<typename Integer>
    inline bool isPowerOf2(Integer n)
    {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    /**
     * Returns the smallest power of 2 greater than n.
     */
    template<typename Integer>
    inline Integer nextPowerOf2(Integer n)
    {
        if (isPowerOf2(n))
        {
            return 2 * n;
        }
        
        #ifdef _MSC_VER 
        size_t size_in_bits = sizeof(Integer) * 8;
        #else
        constexpr size_t size_in_bits = sizeof(Integer) * 8;
        #endif

        for (size_t shift = 1; shift < size_in_bits; shift *= 2)
        {
            n |= (n >> shift);
        }
        return (n + 1);
    }

    /**
     * Prototype of distance calculating functions.
     */
    typedef std::function<double(const std::vector<double>&,
                                 const std::vector<double>&)> DistanceFunctionType;

    /**
     * Returns Euclidean distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Euclidean distance
     */
    template <typename DataType>
    DataType euclideanDistance(const std::vector<DataType>& v1,
                                                  const std::vector<DataType>& v2)
    {
        DataType distance = 0.0;
        for (std::size_t i = 0, size = v1.size(); i < size; i++)
        {
            distance += (v1[i] - v2[i])*(v1[i] - v2[i]);
        }

        return std::sqrt(distance);
    }

    /**
     * Returns Manhattan (taxicab) distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Manhattan distance
     */
    template <typename DataType>
    DataType manhattanDistance(const std::vector<DataType>& v1,
                                                  const std::vector<DataType>& v2)
    {
        DataType distance = 0.0;
        for (std::size_t i = 0, size = v1.size(); i < size; i++)
        {
            distance += std::abs(v1[i] - v2[i]);
        }

        return distance;
    }

    /**
     * Returns Chebyshev distance between two vectors.
     *
     * @param v1 first vector
     * @param v2 second vector
     * @return Chebyshev distance
     */
    template <typename DataType>
    DataType chebyshevDistance(const std::vector<DataType>& v1,
                                                  const std::vector<DataType>& v2)
    {
        DataType distance = 0.0, max = 0.0;
        for (std::size_t i = 0, size = v1.size(); i < size; i++)
        {
            distance = std::abs(v1[i] - v2[i]);
            if (distance > max)
            {
                max = distance;
            }
        }

        return max;
    }

}

#endif // FUNCTIONS_H
