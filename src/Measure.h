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

class Measure
{
public:
    Measure(int32_t mantissa, int32_t exponent)
    {
        _mantissa = mantissa;
        _exponent = exponent;
    };

    uint32_t mantissa() { return _mantissa; };
    uint32_t exponent() { return _exponent; };

    /**
     * Convert scientific notation to float.
     *
     * @warning This can reduce precision.
     */
    float toFloat() { return (float)(_mantissa * pow(10, _exponent)); };

private:
    uint32_t _mantissa;
    uint32_t _exponent;
};

#endif
