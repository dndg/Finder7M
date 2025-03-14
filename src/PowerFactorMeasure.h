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

#ifndef _POWER_FACTOR_MEASURE_H_INCLUDED
#define _POWER_FACTOR_MEASURE_H_INCLUDED

#include <cmath>
#include "Measure.h"

#define POWER_FACTOR_EXPONENT -4

#define INVALID_IMPORT_BITMASK 0x04
#define INVALID_INDUCTIVE_BITMASK 0x08

class PowerFactorMeasure : public Measure
{
public:
    PowerFactorMeasure(bool isImport, bool isInductive, int32_t mantissa, int8_t error)
        : Measure(mantissa, POWER_FACTOR_EXPONENT, error)
    {
        _isImport = isImport;
        _isInductive = isInductive;
    };

    /**
     * Returns true if the measured Power Factor is import.
     */
    bool isImport() { return _isImport; };

    /**
     * Returns true if the measured Power Factor is export.
     */
    bool isExport() { return !_isImport; };

    /**
     * Returns true if the measured Power Factor is inductive.
     */
    bool isInductive() { return _isInductive; };

    /**
     * Returns true if the measured Power Factor is inductive.
     */
    bool isCapacitative() { return !_isInductive; };

    /**
     * Return true if there was an error while reading this Power Factor measure.
     */
    bool isReadError() override
    {
        int8_t errorCode = getErrorCode();
        return Measure::isReadError() || ((errorCode & (INVALID_IMPORT_BITMASK | INVALID_INDUCTIVE_BITMASK)) != 0);
    }

    /**
     * 0x01 = Invalid mantissa.
     * 0x02 = Invalid exponent.
     * 0x03 = Invalid mantissa and exponent or generic read error.
     * 0x04 = Invalid import/export bitmask.
     * 0x08 = Invalid inductive/capacitative bitmask.
     */
    int8_t getErrorCode() override { return Measure::getErrorCode(); }

private:
    bool _isImport;
    bool _isInductive;
};

#endif
