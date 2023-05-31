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
#include <ArduinoRS485.h>
#include <math.h>

#include "Finder7M.h"

boolean Finder7M::init(uint32_t baudrate, uint32_t serialParameters)
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

    RS485.setDelays(preDelay, postDelay);
    ModbusRTUClient.setTimeout(timeout);
    return ModbusRTUClient.begin(baudrate, serialParameters) == 1;
};

bool Finder7M::getSerialNumber(uint8_t address, Finder7MSerialNumber &buffer)
{
    uint8_t attempts = 3;
    while (attempts > 0)
    {
        ModbusRTUClient.requestFrom(address, INPUT_REGISTERS, FINDER_7M_REG_SERIAL_NUMBER, 4);
        uint32_t data1 = ModbusRTUClient.read();
        uint32_t data2 = ModbusRTUClient.read();
        uint32_t data3 = ModbusRTUClient.read();
        uint32_t data4 = ModbusRTUClient.read();
        if (
            data1 != INVALID_DATA &&
            data2 != INVALID_DATA &&
            data3 != INVALID_DATA &&
            data4 != INVALID_DATA)
        {
            buffer[0] = data1 & 0xff00 >> 8;
            buffer[1] = data1 & 0x00ff;

            buffer[2] = data2 & 0xff00 >> 8;
            buffer[3] = data2 & 0x00ff;

            buffer[4] = data3 & 0xff00 >> 8;
            buffer[5] = data3 & 0x00ff;

            buffer[6] = data4 & 0xff00 >> 8;
            buffer[7] = data4 & 0x00ff;
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

uint16_t Finder7M::getSoftwareReference(uint8_t address)
{
    return modbus7MRead16(address, FINDER_7M_REG_SOFTWARE_REFERENCE);
};

uint16_t Finder7M::getHardwareReference(uint8_t address)
{
    return modbus7MRead16(address, FINDER_7M_REG_HARDWARE_REFERENCE);
};

Measure Finder7M::getMIDInActiveEnergy(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E1);
    uint32_t e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E1_EXP);
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDExActiveEnergy(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E2);
    uint32_t e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E2_EXP);
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDInReactiveEnergy(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E3);
    uint32_t e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E3_EXP);
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDExReactiveEnergy(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_E4);
    uint32_t e = modbus7MRead16(address, FINDER_7M_REG_ENERGY_COUNTER_E4_EXP);
    return generateMeasure(m, e);
};

Measure Finder7M::getMIDInActiveEnergyXK(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E1);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDExActiveEnergyXK(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E2);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDInReactiveEnergyXK(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E3);
    return generateMeasure(m, 0);
};

Measure Finder7M::getMIDExReactiveEnergyXK(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_ENERGY_COUNTER_XK_E4);
    return generateMeasure(m, 0);
};

Measure Finder7M::getFrequency(uint8_t address)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_FREQUENCY));
};

Measure Finder7M::getVoltage(uint8_t address)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_U1));
};

Measure Finder7M::getActivePowerTotal(uint8_t address)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_ACTIVE_POWER_TOTAL));
};

Measure Finder7M::getReactivePowerTotal(uint8_t address)
{
    return convertT6(modbus7MRead32(address, FINDER_7M_REG_REACTIVE_POWER_TOTAL));
};

Measure Finder7M::getApparentPowerTotal(uint8_t address)
{
    return convertT5(modbus7MRead32(address, FINDER_7M_REG_APPARENT_POWER_TOTAL));
};

Measure Finder7M::getRunTime(uint8_t address)
{
    uint32_t m = modbus7MRead32(address, FINDER_7M_REG_RUN_TIME);
    return generateMeasure(m, 0);
};

boolean Finder7M::resetCounter(uint8_t address, uint8_t counterNumber)
{
    if (counterNumber < 1 || counterNumber > 16)
    {
        return false;
    }
    uint16_t toWrite = 0x0001 << (counterNumber - 1);
    if (modbus6MWrite16(address, FINDER_7M_REG_RESET_ENERGY, toWrite) == 1)
    {
        boolean res = saveSettings(address);
        return res;
    }
    return false;
};

boolean Finder7M::resetCounters(uint8_t address)
{
    if (modbus6MWrite16(address, FINDER_7M_REG_RESET_ENERGY, 0xFFFF) == 1)
    {
        boolean res = saveSettings(address);
        return res;
    }
    return false;
};

uint32_t Finder7M::modbus7MRead16(uint8_t addr, uint16_t reg)
{
    uint32_t attempts = 3;
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

uint32_t Finder7M::modbus7MRead32(uint8_t addr, uint16_t reg)
{
    uint8_t attempts = 3;
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

boolean Finder7M::modbus6MWrite16(uint8_t address, uint16_t reg, uint16_t toWrite)
{
    uint8_t attempts = 3;
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

boolean Finder7M::saveSettings(uint8_t address)
{
    return modbus6MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0001) == 1;
};

boolean Finder7M::resetSettings(uint8_t address)
{
    return modbus6MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0002) == 1;
};

boolean Finder7M::restartDevice(uint8_t address)
{
    return modbus6MWrite16(address, FINDER_7M_REG_OPERATOR_COMMAND, 0x0003) == 1;
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
