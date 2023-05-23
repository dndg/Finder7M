/**
 * This file is part of Finder 7M for Finder Opta.
 *
 * Finder 7M for Finder Opta is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Lesser General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Finder 7M for Finder Opta is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with Foobar.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _MEASURE_H_INCLUDED
#define _MEASURE_H_INCLUDED

#include <cmath>

#define INVALID_DATA 0xFFFFFFFF

class Measure
{
public:
    Measure(uint32_t mantissa, uint32_t exponent)
    {
        _mantissa = mantissa;
        _exponent = exponent;
    };

    /**
     * Return the measured value mantissa.
     */
    int32_t mantissa() { return _mantissa; };

    /**
     * Return the measured value exponent.
     */
    int16_t exponent() { return (int16_t)_exponent; };

    /**
     * Convert scientific notation to float.
     *
     * @warning This can reduce precision.
     */
    float toFloat() { return (float)(mantissa() * pow(10, exponent())); };

    /**
     * Return true if there was an error while reading this measure.
     */
    bool isReadError() { return _mantissa == INVALID_DATA || _exponent == INVALID_DATA; };

private:
    uint32_t _mantissa;
    uint32_t _exponent;
};

#endif
