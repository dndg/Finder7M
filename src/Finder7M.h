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

#ifndef _FINDER_7_M_H_INCLUDED
#define _FINDER_7_M_H_INCLUDED

#include "Measure.h"

constexpr int FINDER_7M_REF_SERIAL_NUMBER = 9;           // Serial Number                           (T_Str8)
constexpr int FINDER_7M_REF_SOFTWARE_REFERENCE = 13;     // Software Reference                      (T1)
constexpr int FINDER_7M_REF_HARDWARE_REFERENCE = 14;     // Hawrdware Reference                     (T_Str2)
constexpr int FINDER_7M_REG_RUN_TIME = 103;              // Run time                                (T3)
constexpr int FINDER_7M_REG_FREQUENCY = 105;             // Frequency                               (T5)
constexpr int FINDER_7M_REG_U1 = 107;                    // Voltage U1                              (T5)
constexpr int FINDER_7M_REG_U2 = 109;                    // Voltage U2                              (T5)
constexpr int FINDER_7M_REG_U3 = 111;                    // Voltage U3                              (T5)
constexpr int FINDER_7M_REG_ACTIVE_POWER_TOTAL = 140;    // Active Power Total (Pt)                 (T6)
constexpr int FINDER_7M_REG_REACTIVE_POWER_TOTAL = 148;  // Reactive Power Total (Qt)               (T6)
constexpr int FINDER_7M_REG_APPARENT_POWER_TOTAL = 156;  // Apparent Power Total (St)               (T5)
constexpr int FINDER_7M_REG_POWER_FACTOR_TOTAL = 164;    // Power Factor Total (PFt)                (T7)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E1_EXP = 401; // Energy counter E1 Exponent              (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E2_EXP = 402; // Energy counter E2 Exponent              (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E3_EXP = 403; // Energy counter E3 Exponent              (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E4_EXP = 404; // Energy counter E4 Exponent              (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E1 = 406;     // Energy counter E1                       (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E2 = 408;     // Energy counter E2                       (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E3 = 410;     // Energy counter E3                       (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E4 = 412;     // Energy counter E4                       (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E1 = 462;  // Energy counter E1 x 1000                (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E2 = 464;  // Energy counter E2 x 1000                (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E3 = 466;  // Energy counter E3 x 1000                (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E4 = 468;  // Energy counter E4 x 1000                (T3)

constexpr auto MODBUS_BAUDRATE = 19200;
constexpr auto MODBUS_SERIAL_PARAMETERS = SERIAL_8N2;
constexpr auto MODBUS_BIT_DURATION = 1.f / MODBUS_BAUDRATE;
constexpr auto MODBUS_PRE_DELAY = MODBUS_BIT_DURATION * 9.6f * 3.5f * 1e6;  // preDelay in microseconds as per Modbus RTU.
constexpr auto MODBUS_POST_DELAY = MODBUS_BIT_DURATION * 9.6f * 3.5f * 1e6; // postDelay in microseconds as per Modbus RTU.

#define INVALID_DATA 0xFFFFFFFF

typedef unsigned char Finder7MSerialNumber[8];

class Finder7M
{
public:
    Finder7M() {}
    /**
     * Set preDelay and postDelay and start the Modbus RTY client
     * with the parameters for the Finder 7M.
     *
     * @return true in case of success, false otherwise.
     */
    boolean init();
    /**
     * Read serial number of 8 characters and return it into
     * buffer.
     *
     * @param address Modbus address of the target device.
     * @param buffer A buffer of type Finder7MSerialNumber.
     *
     * @return true in case of success, false otherwise.
     */
    bool getSerialNumber(uint8_t address, Finder7MSerialNumber &buffer);
    /**
     * @param address Modbus address of the target device.
     *
     * @return The Software Reference of the device.
     */
    uint16_t getSoftwareReference(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return The Hardware Reference of the device.
     */
    uint16_t getHardwareReference(uint8_t address);

    /**
     * Read the Import Active Energy from the
     * MID certified energy counter E1.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDInActiveEnergy(uint8_t address);
    /**
     * Read the Export Active Energy from the
     * MID certified energy counter E2.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDExActiveEnergy(uint8_t address);
    /**
     * Read the Import Reactive Energy from the
     * MID certified energy counter E3.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDInReactiveEnergy(uint8_t address);
    /**
     * Read the Export Reactive Energy from the
     * MID certified energy counter E4.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDExReactiveEnergy(uint8_t address);

    /**
     * Read the Import Active Energy multiplied by 1000.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDInActiveEnergyXK(uint8_t address);
    /**
     * Read the Export Active Energy multiplied by 1000.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDExActiveEnergyXK(uint8_t address);
    /**
     * Read the Import Reactive Energy multiplied by 1000.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDInReactiveEnergyXK(uint8_t address);
    /**
     * Read the Export Reactive Energy multiplied by 1000.
     *
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the value.
     */
    Measure getMIDExReactiveEnergyXK(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the frequency measured
     * on the device.
     */
    Measure getFrequency(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the voltage measured
     * on the device.
     */
    Measure getVoltage(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the Active Power
     * Total (Pt) measured on the device.
     */
    Measure getActivePowerTotal(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the Reactive Power
     * Total (Qt) measured on the device.
     */
    Measure getReactivePowerTotal(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the Apparent Power
     * Total (St) measured on the device.
     */
    Measure getApparentPowerTotal(uint8_t address);
    /**
     * @param address Modbus address of the target device.
     *
     * @return A Measure containing the run time of the device.
     */
    Measure getRunTime(uint8_t address);
    /**
     * Read a 16-bits register.
     *
     * @param addr Modbus id of the target device.
     * @param reg Start address of the register.
     *
     * @return The read value or INVALID_DATA.
     */
    uint32_t modbus7MRead16(uint8_t addr, uint16_t reg);
    /**
     * Read two consecutive 16-bits registers and compose them
     * into a single 32-bits value, by shifting the first value
     * left by 16 bits.
     *
     * @param addr Modbus id of the target device.
     * @param reg Start address of the register.
     *
     * @return The composed value or INVALID_DATA.
     */
    uint32_t modbus7MRead32(uint8_t addr, uint16_t reg);

    /** Convert T5 encoding to Measure.*/
    Measure convertT5(uint32_t n);
    /** Convert T6 encoding to Measure.*/
    Measure convertT6(uint32_t n);
};

#endif
