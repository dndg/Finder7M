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

#include <ArduinoModbus.h>
#include <math.h>

#include "Finder7M.h"

bool Finder7M::init(uint32_t baudrate, uint32_t serialParameters, uint32_t timeoutMs)
{
    uint32_t preDelay, postDelay, timeout;
    float bitDuration = 1.f / baudrate;

    if (baudrate <= 19200)
    {
        preDelay = postDelay = bitDuration * 9.6f * 3.5f * 1e6;
        timeout = 200;
    }
    else
    {
        preDelay = postDelay = 1750;
        timeout = 1000;
    }

    if (timeoutMs > 0)
    {
        timeout = timeoutMs;
    }

    RS485.setDelays(preDelay, postDelay);
    ModbusRTUClient.setTimeout(timeout);
    return ModbusRTUClient.begin(baudrate, serialParameters) == 1;
};

void Finder7M::setTimeout(uint32_t timeoutMs)
{
    ModbusRTUClient.setTimeout(timeoutMs);
};

bool Finder7M::getModelNumber(uint8_t address, Finder7MModelNumber &buffer, uint8_t attempts)
{
    while (attempts > 0)
    {
        ModbusRTUClient.requestFrom(address, INPUT_REGISTERS, FINDER_7M_REG_MODEL_NUMBER, 8);
        uint32_t data;
        bool validData = true;

        for (int i = 0; i < 8; i++)
        {
            data = ModbusRTUClient.read();
            if (data == INVALID_DATA)
            {
                validData = false;
                break;
            }
            buffer[2 * i] = (data & 0xff00) >> 8;
            buffer[2 * i + 1] = data & 0x00ff;
        }

        if (validData)
        {
            return true;
        }
        attempts -= 1;
        delay(10);
    }
    return false;
}

bool Finder7M::getSerialNumber(uint8_t address, Finder7MSerialNumber &buffer, uint8_t attempts)
{
    while (attempts > 0)
    {
        ModbusRTUClient.requestFrom(address, INPUT_REGISTERS, FINDER_7M_REG_SERIAL_NUMBER, 4);
        uint32_t data;
        bool validData = true;

        for (int i = 0; i < 4; i++)
        {
            data = ModbusRTUClient.read();
            if (data == INVALID_DATA)
            {
                validData = false;
                break;
            }
            buffer[2 * i] = (data & 0xff00) >> 8;
            buffer[2 * i + 1] = data & 0x00ff;
        }

        if (validData)
        {
            return true;
        }
        attempts -= 1;
        delay(10);
    }
    return false;
}

uint16_t Finder7M::getSoftwareReference(uint8_t address, uint8_t attempts)
{
    return modbus7MRead16(address, FINDER_7M_REG_SOFTWARE_REFERENCE, attempts);
};

uint16_t Finder7M::getHardwareReference(uint8_t address, uint8_t attempts)
{
    return modbus7MRead16(address, FINDER_7M_REG_HARDWARE_REFERENCE, attempts);
};

Measure Finder7M::getMIDInActiveEnergy(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E1, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E1_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDExActiveEnergy(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E2, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E2_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDInReactiveEnergy(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E3, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E3_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDExReactiveEnergy(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E4, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E4_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDInActiveEnergyXK(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E1, attempts);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDExActiveEnergyXK(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E2, attempts);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDInReactiveEnergyXK(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E3, attempts);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDExReactiveEnergyXK(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E4, attempts);
    return generateMeasure(m, 0);
};

Measure Finder7M::getFrequency(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_FREQUENCY, attempts));
};

Measure Finder7M::getVoltage(uint8_t address, uint8_t attempts)
{
    return getVoltagePhase1(address, attempts);
};

Measure Finder7M::getVoltagePhase1(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_U1, attempts));
};

Measure Finder7M::getVoltagePhase2(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_U2, attempts));
};

Measure Finder7M::getVoltagePhase3(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_U3, attempts));
};

Measure Finder7M::getCurrent(uint8_t address, uint8_t attempts)
{
    return getCurrentPhase1(address, attempts);
};

Measure Finder7M::getCurrentPhase1(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_I1, attempts));
};

Measure Finder7M::getCurrentPhase2(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_I2, attempts));
};

Measure Finder7M::getCurrentPhase3(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_I3, attempts));
};

Measure Finder7M::getActivePowerTotal(uint8_t address, uint8_t attempts)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_ACTIVE_POWER_TOTAL, attempts));
};

Measure Finder7M::getActivePowerPhase1(uint8_t address, uint8_t attempts)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_ACTIVE_POWER_PHASE_1, attempts));
}

Measure Finder7M::getActivePowerPhase2(uint8_t address, uint8_t attempts)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_ACTIVE_POWER_PHASE_2, attempts));
}

Measure Finder7M::getActivePowerPhase3(uint8_t address, uint8_t attempts)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_ACTIVE_POWER_PHASE_3, attempts));
}

Measure Finder7M::getReactivePowerTotal(uint8_t address, uint8_t attempts)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_REACTIVE_POWER_TOTAL, attempts));
};

Measure Finder7M::getApparentPowerTotal(uint8_t address, uint8_t attempts)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_APPARENT_POWER_TOTAL, attempts));
};

Measure Finder7M::getEnergyCounterC1(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C1, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C1_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC2(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C2, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C2_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC3(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C3, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C3_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC4(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C4, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C4_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC5(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C5, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C5_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC6(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C6, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C6_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC7(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C7, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C7_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC8(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C8, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C8_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC9(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C9, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C9_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC10(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C10, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C10_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC11(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C11, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C11_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC12(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C12, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C12_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC13(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C13, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C13_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC14(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C14, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C14_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC15(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C15, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C15_EXP, attempts);
    }
    return generateMeasure(m, e);
};

Measure Finder7M::getEnergyCounterC16(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_C16, attempts);
    uint32_t e = 0;
    if (m != INVALID_DATA)
    {
        e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_C16_EXP, attempts);
    }
    return generateMeasure(m, e);
};

PowerFactorMeasure Finder7M::getPowerFactorTotal(uint8_t address, uint8_t attempts)
{
    uint32_t pf = modbus7MRead32(address, FINDER_7M_REG_POWER_FACTOR_TOTAL, attempts);
    return convertT7(pf);
}

PowerFactorMeasure Finder7M::getPowerFactorPhase1(uint8_t address, uint8_t attempts)
{
    uint32_t pf = modbus7MRead32(address, FINDER_7M_REG_POWER_FACTOR_PHASE_1, attempts);
    return convertT7(pf);
}

PowerFactorMeasure Finder7M::getPowerFactorPhase2(uint8_t address, uint8_t attempts)
{
    uint32_t pf = modbus7MRead32(address, FINDER_7M_REG_POWER_FACTOR_PHASE_2, attempts);
    return convertT7(pf);
}

PowerFactorMeasure Finder7M::getPowerFactorPhase3(uint8_t address, uint8_t attempts)
{
    uint32_t pf = modbus7MRead32(address, FINDER_7M_REG_POWER_FACTOR_PHASE_3, attempts);
    return convertT7(pf);
}

Measure Finder7M::getRunTime(uint8_t address, uint8_t attempts)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_RUN_TIME, attempts);
    return generateMeasure(m, 0);
};

bool Finder7M::resetCounter(uint8_t address, uint8_t counterNumber, uint8_t attempts)
{
    if (counterNumber < 1 || counterNumber > 16)
    {
        return false;
    }
    uint16_t toWrite = 0x0001 << (counterNumber - 1);
    if (modbus7MWrite16(address, FINDER_7M_REG_RESET_ENERGY, toWrite, attempts) == 1)
    {
        bool res = saveSettings(address);
        return res;
    }
    return false;
};

bool Finder7M::resetCounters(uint8_t address, uint8_t attempts)
{
    if (modbus7MWrite16(address, FINDER_7M_REG_RESET_ENERGY, 0xFFFF, attempts) == 1)
    {
        bool res = saveSettings(address);
        return res;
    }
    return false;
};

uint32_t Finder7M::modbus7MRead16(uint8_t addr, uint16_t reg, uint8_t attempts)
{
    while (attempts > 0)
    {
        ModbusRTUClient.requestFrom(addr, INPUT_REGISTERS, reg, 1);
        uint32_t data = ModbusRTUClient.read();
        if (data != INVALID_DATA)
        {
            return data;
        }
        else
        {
            attempts -= 1;
            delay(10);
        }
    }
    return INVALID_DATA;
};

uint32_t Finder7M::modbus7MRead32(uint8_t addr, uint16_t reg, uint8_t attempts)
{
    while (attempts > 0)
    {
        ModbusRTUClient.requestFrom(addr, INPUT_REGISTERS, reg, 2);
        uint32_t data1 = ModbusRTUClient.read();
        uint32_t data2 = ModbusRTUClient.read();
        if (data1 != INVALID_DATA && data2 != INVALID_DATA)
        {
            return data1 << 16 | data2;
        }
        else
        {
            attempts -= 1;
            delay(10);
        }
    }
    return INVALID_DATA;
};

bool Finder7M::modbus7MWrite16(uint8_t address, uint16_t reg, uint16_t toWrite, uint8_t attempts)
{
    while (attempts > 0)
    {
        if (ModbusRTUClient.holdingRegisterWrite(address, reg, toWrite) == 1)
        {
            return true;
        }
        else
        {
            attempts -= 1;
            delay(10);
        }
    }
    return false;
};

Measure Finder7M::convertT5(uint32_t n)
{
    if (n != INVALID_DATA)
    {
        uint32_t s = (n & 0x80000000) >> 31;
        int32_t e = (n & 0x7F000000) >> 24;
        if (s == 1)
        {
            e = e - 0x80;
        }
        e = (e & 0x0000FFFF);
        uint32_t m = n & 0x00FFFFFF;
        return generateMeasure(m, e);
    }
    return Measure(0, 0, INVALID_READ);
};

Measure Finder7M::convertT6(uint32_t n)
{
    if (n != INVALID_DATA)
    {
        uint32_t s = (n & 0x80000000) >> 31;
        int32_t e = (n & 0x7F000000) >> 24;
        if (s == 1)
        {
            e = e - 0x80;
        }
        e = (e & 0x0000FFFF);
        uint32_t ms = (n & 0x00800000) >> 23;
        int32_t mv = (n & 0x007FFFFF);
        if (ms == 1)
        {
            mv = mv - 0x800000;
        }
        return generateMeasure(mv, e);
    }
    return Measure(0, 0, INVALID_READ);
};

PowerFactorMeasure Finder7M::convertT7(uint32_t n)
{
    if (n != INVALID_DATA)
    {
        bool isImport;
        switch ((n & 0xFF000000) >> 24)
        {
        case 0x00:
            isImport = true;
            break;
        case 0xFF:
            isImport = false;
            break;
        default:
            return PowerFactorMeasure(true, true, 0, INVALID_IMPORT_BITMASK);
        }

        bool isInductive;
        switch ((n & 0x00FF0000) >> 16)
        {
        case 0x00:
            isInductive = true;
            break;
        case 0xFF:
            isInductive = false;
            break;
        default:
            return PowerFactorMeasure(true, true, 0, INVALID_INDUCTIVE_BITMASK);
        }

        int32_t mv = (n & 0x0000FFFF);
        return PowerFactorMeasure(isImport, isInductive, mv, 0);
    }
    return PowerFactorMeasure(true, true, 0, INVALID_READ);
};

bool Finder7M::saveSettings(uint8_t address, uint8_t attempts)
{
    return modbus7MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0001, attempts) == 1;
};

bool Finder7M::resetSettings(uint8_t address, uint8_t attempts)
{
    return modbus7MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0002, attempts) == 1;
};

bool Finder7M::restartDevice(uint8_t address, uint8_t attempts)
{
    return modbus7MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0003, attempts) == 1;
};

Measure Finder7M::generateMeasure(uint32_t mantissa, uint32_t exponent)
{
    if (mantissa == INVALID_DATA && exponent == INVALID_DATA)
    {
        return Measure(0, 0, INVALID_READ);
    }
    if (mantissa == INVALID_DATA)
    {
        return Measure(0, exponent, INVALID_MANTISSA);
    }
    if (exponent == INVALID_DATA)
    {
        return Measure(mantissa, 0, INVALID_EXPONENT);
    }
    return Measure((int32_t)mantissa, (int16_t)exponent, 0);
};
