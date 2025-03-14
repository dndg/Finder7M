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

#define INVALID_MANTISSA 0x01
#define INVALID_EXPONENT 0x02
#define INVALID_READ 0x03

class Measure
{
public:
    Measure(int32_t mantissa, int16_t exponent, int8_t error)
    {
        _mantissa = mantissa;
        _exponent = exponent;
        _error = error;
    };

    /**
     * Return the measured value mantissa.
     */
    int32_t mantissa() { return _mantissa; };

    /**
     * Return the measured value exponent.
     */
    int16_t exponent() { return _exponent; };

    /**
     * Convert scientific notation to float.
     *
     * @warning This can reduce precision.
     */
    float toFloat() { return (float)(mantissa() * pow(10, exponent())); };

    /**
     * Return true if there was an error while reading this measure.
     */
    virtual bool isReadError() { return (_error & INVALID_READ) > 0; };

    /**
     * 0x01 = Invalid mantissa.
     * 0x02 = Invalid exponent.
     * 0x03 = Invalid mantissa and exponent or generic read error.
     */
    virtual int8_t getErrorCode() { return _error; };

private:
    int32_t _mantissa;
    int16_t _exponent;
    int8_t _error;
};

#endif
