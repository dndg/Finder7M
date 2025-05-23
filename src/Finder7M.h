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

#include <ArduinoRS485.h>

#include "Measure.h"
#include "PowerFactorMeasure.h"

constexpr int FINDER_7M_REG_MODEL_NUMBER = 1;             // Model Number                                    (T_Str16)
constexpr int FINDER_7M_REG_SERIAL_NUMBER = 9;            // Serial Number                                   (T_Str8)
constexpr int FINDER_7M_REG_SOFTWARE_REFERENCE = 13;      // Software Reference                              (T1)
constexpr int FINDER_7M_REG_HARDWARE_REFERENCE = 14;      // Hardware Reference                              (T_Str2)
constexpr int FINDER_7M_REG_PHASE_VALID_MEAS = 101;       // Phase valid measurement                         (T1)
constexpr int FINDER_7M_REG_RUN_TIME = 103;               // Run time                                        (T3)
constexpr int FINDER_7M_REG_FREQUENCY = 105;              // Frequency                                       (T5)
constexpr int FINDER_7M_REG_U1 = 107;                     // Voltage U1                                      (T5)
constexpr int FINDER_7M_REG_U2 = 109;                     // Voltage U2                                      (T5)
constexpr int FINDER_7M_REG_U3 = 111;                     // Voltage U3                                      (T5)
constexpr int FINDER_7M_REG_U_AVG_PN = 113;               // Average Voltage Phase-Neutral                   (T5)
constexpr int FINDER_7M_REG_J_U12 = 115;                  // Phase angle between U1 and U2                   (T17)
constexpr int FINDER_7M_REG_J_U23 = 116;                  // Phase angle between U2 and U3                   (T17)
constexpr int FINDER_7M_REG_J_U31 = 117;                  // Phase angle between U3 and U1                   (T17)
constexpr int FINDER_7M_REG_U12 = 118;                    // Voltage U12                                     (T5)
constexpr int FINDER_7M_REG_U23 = 120;                    // Voltage U23                                     (T5)
constexpr int FINDER_7M_REG_U31 = 122;                    // Voltage U31                                     (T5)
constexpr int FINDER_7M_REG_U_AVG_PP = 124;               // Average Voltage Phase-Phase                     (T5)
constexpr int FINDER_7M_REG_I1 = 126;                     // Current I1                                      (T5)
constexpr int FINDER_7M_REG_I2 = 128;                     // Current I2                                      (T5)
constexpr int FINDER_7M_REG_I3 = 130;                     // Current I3                                      (T5)
constexpr int FINDER_7M_REG_I_AVG = 136;                  // Average Current                                 (T5)
constexpr int FINDER_7M_REG_SI = 138;                     // SI                                              (T5)
constexpr int FINDER_7M_REG_ACTIVE_POWER_TOTAL = 140;     // Active Power Total (Pt)                         (T6)
constexpr int FINDER_7M_REG_ACTIVE_POWER_PHASE_1 = 142;   // Active Power Phase 1 (P1)                       (T6)
constexpr int FINDER_7M_REG_ACTIVE_POWER_PHASE_2 = 144;   // Active Power Phase 2 (P2)                       (T6)
constexpr int FINDER_7M_REG_ACTIVE_POWER_PHASE_3 = 146;   // Active Power Phase 3 (P3)                       (T6)
constexpr int FINDER_7M_REG_REACTIVE_POWER_TOTAL = 148;   // Reactive Power Total (Qt)                       (T6)
constexpr int FINDER_7M_REG_REACTIVE_POWER_PHASE_1 = 150; // Reactive Power Phase 1 (Q1)                     (T6)
constexpr int FINDER_7M_REG_REACTIVE_POWER_PHASE_2 = 152; // Reactive Power Phase 2 (Q2)                     (T6)
constexpr int FINDER_7M_REG_REACTIVE_POWER_PHASE_3 = 154; // Reactive Power Phase 3 (Q3)                     (T6)
constexpr int FINDER_7M_REG_APPARENT_POWER_TOTAL = 156;   // Apparent Power Total (St)                       (T5)
constexpr int FINDER_7M_REG_APPARENT_POWER_PHASE_1 = 158; // Apparent Power Phase 1 (S1)                     (T5)
constexpr int FINDER_7M_REG_APPARENT_POWER_PHASE_2 = 160; // Apparent Power Phase 2 (S2)                     (T5)
constexpr int FINDER_7M_REG_APPARENT_POWER_PHASE_3 = 162; // Apparent Power Phase 3 (S3)                     (T5)
constexpr int FINDER_7M_REG_POWER_FACTOR_TOTAL = 164;     // Power Factor Total (PFt)                        (T7)
constexpr int FINDER_7M_REG_POWER_FACTOR_PHASE_1 = 166;   // Power Factor Phase 1 (PF1)                      (T7)
constexpr int FINDER_7M_REG_POWER_FACTOR_PHASE_2 = 168;   // Power Factor Phase 2 (PF2)                      (T7)
constexpr int FINDER_7M_REG_POWER_FACTOR_PHASE_3 = 170;   // Power Factor Phase 3 (PF3)                      (T7)
constexpr int FINDER_7M_REG_POWER_ANGLE_TOTAL = 172;      // Power Angle Total (atan2(Pt,Qt))                (T17)
constexpr int FINDER_7M_REG_J_U1_I1 = 173;                // Angle between U1 and I1                         (T17)
constexpr int FINDER_7M_REG_J_U2_I2 = 174;                // Angle between U2 and I2                         (T17)
constexpr int FINDER_7M_REG_J_U3_I3 = 175;                // Angle between U3 and I3                         (T17)
constexpr int FINDER_7M_REG_INTERNAL_TEMPERATURE = 181;   // Internal temeperature                           (T17)
constexpr int FINDER_7M_REG_THD_U1 = 182;                 // U1 THD%                                         (T16)
constexpr int FINDER_7M_REG_THD_U2 = 183;                 // U2 THD%                                         (T16)
constexpr int FINDER_7M_REG_THD_U3 = 184;                 // U3 THD%                                         (T16)
constexpr int FINDER_7M_REG_THD_I1 = 188;                 // I1 THD%                                         (T16)
constexpr int FINDER_7M_REG_THD_I2 = 189;                 // I2 THD%                                         (T16)
constexpr int FINDER_7M_REG_THD_I3 = 190;                 // I3 THD%                                         (T16)
constexpr int FINDER_7M_REG_ALARM_STATUS_FLAGS_G12 = 191; // Alarm Status Flags (G1, G2)                     (T1)
constexpr int FINDER_7M_REG_ALARM_STATUS_FLAGS_G34 = 192; // Alarm Status Flags (G3, G4)                     (T1)
constexpr int FINDER_7M_REG_IO_1 = 193;                   // IO 1 Value                                      (T17)
constexpr int FINDER_7M_REG_IO_2 = 194;                   // IO 2 Value                                      (T17)
constexpr int FINDER_7M_REG_IO_3 = 195;                   // IO 3 Value                                      (T17)
constexpr int FINDER_7M_REG_EXTERNAL_RELAY_STATUS = 197;  // External relay status                           (T1)
constexpr int FINDER_7M_REG_ALARM_STATUS_FLAGS_GE = 200;  // Alarm Status Flags (GE)                         (T1)
constexpr int FINDER_7M_REG_LOGIC_FUNCTIONS_VALUES = 201; // Logic functions values                          (T1)
constexpr int FINDER_7M_REG_ACTUAL_TIME = 396;            // Actual time                                     (T_Time)
constexpr int FINDER_7M_REG_CHECKSUM_STATUS = 400;        // Checksum Status                                 (T1)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E1_EXP = 401;  // Energy counter E1 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E2_EXP = 402;  // Energy counter E2 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E3_EXP = 403;  // Energy counter E3 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E4_EXP = 404;  // Energy counter E4 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E1 = 406;      // Energy counter E1                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E2 = 408;      // Energy counter E2                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E3 = 410;      // Energy counter E3                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_E4 = 412;      // Energy counter E4                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C1 = 414;      // Energy counter C1                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C2 = 416;      // Energy counter C2                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C3 = 418;      // Energy counter C3                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C4 = 420;      // Energy counter C4                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C5 = 422;      // Energy counter C5                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C6 = 424;      // Energy counter C6                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C7 = 426;      // Energy counter C7                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C8 = 428;      // Energy counter C8                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C9 = 430;      // Energy counter C9                               (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C10 = 432;     // Energy counter C10                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C11 = 434;     // Energy counter C11                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C12 = 436;     // Energy counter C12                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C13 = 438;     // Energy counter C13                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C14 = 440;     // Energy counter C14                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C15 = 442;     // Energy counter C15                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C16 = 444;     // Energy counter C16                              (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C1_EXP = 446;  // Energy counter C1 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C2_EXP = 447;  // Energy counter C2 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C3_EXP = 448;  // Energy counter C3 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C4_EXP = 449;  // Energy counter C4 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C5_EXP = 450;  // Energy counter C5 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C6_EXP = 451;  // Energy counter C6 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C7_EXP = 452;  // Energy counter C7 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C8_EXP = 453;  // Energy counter C8 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C9_EXP = 454;  // Energy counter C9 Exponent                      (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C10_EXP = 455; // Energy counter C10 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C11_EXP = 456; // Energy counter C11 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C12_EXP = 457; // Energy counter C12 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C13_EXP = 458; // Energy counter C13 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C14_EXP = 459; // Energy counter C14 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C15_EXP = 460; // Energy counter C15 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_C16_EXP = 461; // Energy counter C16 Exponent                     (T2)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E1 = 462;   // Energy counter E1 x 1000                        (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E2 = 464;   // Energy counter E2 x 1000                        (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E3 = 466;   // Energy counter E3 x 1000                        (T3)
constexpr int FINDER_7M_REG_ENERGY_COUNTER_XK_E4 = 468;   // Energy counter E4 x 1000                        (T3)
constexpr int FINDER_7M_REG_OPERATOR_COMMAND = 12;        // Operator command register                       (T1)
constexpr int FINDER_7M_REG_RESET_ENERGY = 31;            // Reset energy command register                   (T1)

#define INVALID_DATA 0xFFFFFFFF

typedef unsigned char Finder7MSerialNumber[8];
typedef unsigned char Finder7MModelNumber[16];

class Finder7M
{
public:
    Finder7M() {}
    /**
     * Set preDelay and postDelay and start the Modbus RTU client
     * with the parameters for the Finder 7M.
     *
     * @param baudrate Defaults to 38400, if not specified.
     * @param serialParameters Defaults to 8N1, if not specified.
     * @param timeoutMs Timeout in ms, if not specified the function
     * will internally use the best value according to Modbus specs.
     *
     * @return true in case of success, false otherwise.
     */
    bool init(uint32_t baudrate = 38400, uint32_t serialParameters = SERIAL_8N1, uint32_t timeoutMs = 0);
    /**
     * Set the Modbus RTU client timeout.
     *
     * @param timeoutMs Timeout in ms.
     */
    void setTimeout(uint32_t timeoutMs);
    /**
     * Read model number of 16 characters and return it into
     * buffer.
     *
     * @param address Modbus address of the target device.
     * @param buffer A buffer of type Finder7MModelNumber.
     * @param attempts Number of attempts before returning error.
     *
     * @return true in case of success, false otherwise.
     */
    bool getModelNumber(uint8_t address, Finder7MModelNumber &buffer, uint8_t attempts = 3);
    /**
     * Read serial number of 8 characters and return it into
     * buffer.
     *
     * @param address Modbus address of the target device.
     * @param buffer A buffer of type Finder7MSerialNumber.
     * @param attempts Number of attempts before returning error.
     *
     * @return true in case of success, false otherwise.
     */
    bool getSerialNumber(uint8_t address, Finder7MSerialNumber &buffer, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return The Software Reference of the device.
     */
    uint16_t getSoftwareReference(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return The Hardware Reference of the device.
     */
    uint16_t getHardwareReference(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Import Active Energy from the
     * MID certified energy counter E1.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in Wh.
     */
    Measure getMIDInActiveEnergy(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Export Active Energy from the
     * MID certified energy counter E2.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in Wh.
     */
    Measure getMIDExActiveEnergy(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Import Reactive Energy from the
     * MID certified energy counter E3.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in varh.
     */
    Measure getMIDInReactiveEnergy(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Export Reactive Energy from the
     * MID certified energy counter E4.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in varh.
     */
    Measure getMIDExReactiveEnergy(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Import Active Energy multiplied by 100.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in 0,1*Wh.
     *
     * @warning Despite the name the x1000 registers are actually
     * multiplied by 100 as their unit of measure is the unit of measure
     * of the corresponding MID register multiplied by 10^(-1).
     * In this case the value is expressed in 0,1*Wh.
     */
    Measure getMIDInActiveEnergyXK(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Export Active Energy multiplied by 100.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in 0,1*Wh.
     *
     * @warning Despite the name the x1000 registers are actually
     * multiplied by 100 as their unit of measure is the unit of measure
     * of the corresponding MID register multiplied by 10^(-1).
     * In this case the value is expressed in 0,1*Wh.
     */
    Measure getMIDExActiveEnergyXK(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Import Reactive Energy multiplied by 100.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in 0,1*varh.
     *
     * @warning Despite the name the x1000 registers are actually
     * multiplied by 100 as their unit of measure is the unit of measure
     * of the corresponding MID register multiplied by 10^(-1).
     * In this case the value is expressed in 0,1*varh.
     */
    Measure getMIDInReactiveEnergyXK(uint8_t address, uint8_t attempts = 3);
    /**
     * Read the Export Reactive Energy multiplied by 100.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value in 0,1*varh.
     *
     * @warning Despite the name the x1000 registers are actually
     * multiplied by 100 as the measure is the unit of measure
     * of the corresponding MID register multiplied by 10^(-1).
     * In this case the value is expressed in 0,1*varh.
     */
    Measure getMIDExReactiveEnergyXK(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the frequency measured
     * on the device.
     */
    Measure getFrequency(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the voltage measured on the
     * device. For the 7M38 model, it is equivalent to the voltage
     * on Phase 1.
     */
    Measure getVoltage(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the voltage on Phase 1.
     */
    Measure getVoltagePhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the voltage on Phase 2.
     */
    Measure getVoltagePhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     * on the device.
     *
     * @return A Measure containing the voltage on Phase 3.
     */
    Measure getVoltagePhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the phase-phase voltage on
     * Phase 1 and Phase 2.
     */
    Measure getVoltagePhase12(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the phase-phase voltage on
     * Phase 2 and Phase 3.
     */
    Measure getVoltagePhase23(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     * on the device.
     *
     * @return A Measure containing the phase-phase voltage on
     * Phase 3 and Phase 1.
     */
    Measure getVoltagePhase31(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     * on the device.
     *
     * @return A Measure containing the phase angle between voltage
     * on Phase 1 and Phase 2.
     */
    Measure getPhaseAngleVoltage12(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     * on the device.
     *
     * @return A Measure containing the phase angle between voltage
     * on Phase 2 and Phase 3.
     */
    Measure getPhaseAngleVoltage23(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     * on the device.
     *
     * @return A Measure containing the phase angle between voltage
     * on Phase 2 and Phase 3.
     */
    Measure getPhaseAngleVoltage31(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the current measured on the
     * device. For the 7M38 model, it is equivalent to the current
     * on Phase 1.
     */
    Measure getCurrent(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the current on Phase 1.
     */
    Measure getCurrentPhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the current on Phase 2.
     */
    Measure getCurrentPhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the current on Phase 3.
     */
    Measure getCurrentPhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Active Power
     * Total (Pt) measured on the device.
     */
    Measure getActivePowerTotal(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Active Power
     * Phase 1 (P1) measured on the device.
     */
    Measure getActivePowerPhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Active Power
     * Phase 2 (P2) measured on the device.
     */
    Measure getActivePowerPhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Active Power
     * Phase 3 (P3) measured on the device.
     */
    Measure getActivePowerPhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Reactive Power
     * Total (Qt) measured on the device.
     */
    Measure getReactivePowerTotal(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Reactive Power
     * Phase 1 (Q1) measured on the device.
     */
    Measure getReactivePowerPhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Reactive Power
     * Phase 2 (Q2) measured on the device.
     */
    Measure getReactivePowerPhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Reactive Power
     * Phase 3 (Q3) measured on the device.
     */
    Measure getReactivePowerPhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Apparent Power
     * Total (St) measured on the device.
     */
    Measure getApparentPowerTotal(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Apparent Power
     * Phase 1 (S1) measured on the device.
     */
    Measure getApparentPowerPhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Apparent Power
     * Phase 2 (S2) measured on the device.
     */
    Measure getApparentPowerPhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Apparent Power
     * Phase 3 (S3) measured on the device.
     */
    Measure getApparentPowerPhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Power Angle
     * Total (atan2(Pt,Qt)) measured on the device.
     */
    Measure getPowerAngleTotal(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Internal
     * Temperature of the device.
     */
    Measure getInternalTemperature(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-1 voltage.
     */
    Measure getVoltagePhase1THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-2 voltage.
     */
    Measure getVoltagePhase2THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-3 voltage.
     */
    Measure getVoltagePhase3THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-1 current.
     */
    Measure getCurrentPhase1THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-2 current.
     */
    Measure getCurrentPhase2THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the Total
     * Harmonic Distortion (THD) of the Phase-3 current.
     */
    Measure getCurrentPhase3THD(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the run time of the device.
     */
    Measure getRunTime(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C1.
     */
    Measure getEnergyCounterC1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C2.
     */
    Measure getEnergyCounterC2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C3.
     */
    Measure getEnergyCounterC3(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C4.
     */
    Measure getEnergyCounterC4(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C5.
     */
    Measure getEnergyCounterC5(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C6.
     */
    Measure getEnergyCounterC6(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C7.
     */
    Measure getEnergyCounterC7(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C8.
     */
    Measure getEnergyCounterC8(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C9.
     */
    Measure getEnergyCounterC9(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C10.
     */
    Measure getEnergyCounterC10(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C11.
     */
    Measure getEnergyCounterC11(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C12.
     */
    Measure getEnergyCounterC12(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C13.
     */
    Measure getEnergyCounterC13(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C14.
     */
    Measure getEnergyCounterC14(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C15.
     */
    Measure getEnergyCounterC15(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A Measure containing the value of the programmable
     * energy counter C16.
     */
    Measure getEnergyCounterC16(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A PowerFactorMeasure containing the total Power Factor
     * (PFt) measured on the device.
     */
    PowerFactorMeasure getPowerFactorTotal(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A PowerFactorMeasure containing the Power Factor
     * Phase 1 (PF1) measured on the device.
     *
     * @warning The Power Factor Phase registers contain value 10000 as
     * mantissa when phase is not connected.
     */
    PowerFactorMeasure getPowerFactorPhase1(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A PowerFactorMeasure containing the total Power Factor
     * Phase 2 (PF2) measured on the device.
     *
     * @warning The Power Factor Phase registers contain value 10000 as
     * mantissa when phase is not connected.
     */
    PowerFactorMeasure getPowerFactorPhase2(uint8_t address, uint8_t attempts = 3);
    /**
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return A PowerFactorMeasure containing the total Power Factor
     * Phase 3 (PF3) measured on the device.
     *
     * @warning The Power Factor Phase registers contain value 10000 as
     * mantissa when phase is not connected.
     */
    PowerFactorMeasure getPowerFactorPhase3(uint8_t address, uint8_t attempts = 3);
    /**
     * Reset a given energy counter on the target device.
     *
     * @param address Modbus address of the target device.
     * @param counterNumber Number of the energy counter that will be reset.
     * @param attempts Number of attempts before returning error.
     *
     * @return true in case of success, false otherwise.
     *
     * @warning Counter resets are executed immediately so you don't need to
     * save settings afterwards.
     */
    bool resetCounter(uint8_t address, uint8_t counterNumber, uint8_t attempts = 3);
    /**
     * Reset all energy counters on the target device.
     *
     * @param address Modbus address of the target device.
     * @param attempts Number of attempts before returning error.
     *
     * @return true in case of success, false otherwise.
     *
     * @warning Counter resets are executed immediately so you don't need to
     * save settings afterwards.
     */
    bool resetCounters(uint8_t address, uint8_t attempts = 3);
    /**
     * Read a 16-bits register.
     *
     * @param addr Modbus id of the target device.
     * @param reg Start address of the register.
     * @param attempts Number of attempts before returning error.
     *
     * @return The read value or INVALID_DATA.
     */
    uint32_t modbus7MRead16(uint8_t addr, uint16_t reg, uint8_t attempts = 3);
    /**
     * Read two consecutive 16-bits registers and compose them
     * into a single 32-bits value, by shifting the first value
     * left by 16 bits.
     *
     * @param addr Modbus id of the target device.
     * @param reg Start address of the register.
     * @param attempts Number of attempts before returning error.
     *
     * @return The composed value or INVALID_DATA.
     */
    uint32_t modbus7MRead32(uint8_t addr, uint16_t reg, uint8_t attempts = 3);
    /**
     * Write 8-bits or 16-bits values to a given register.
     *
     * @param address Modbus id of the target device.
     * @param reg Start address of the destination register.
     * @param toWrite Content that will be written to the destination register.
     * @param attempts Number of attempts before returning error.
     *
     * @return true in case of success, false otherwise.
     */
    bool modbus7MWrite16(uint8_t address, uint16_t reg, uint16_t toWrite, uint8_t attempts = 3);
    /** Convert T5 encoding to Measure.*/
    Measure convertT5(uint32_t n);
    /** Convert T6 encoding to Measure.*/
    Measure convertT6(uint32_t n);
    /** Convert T7 encoding to PowerFactorMeasure.*/
    PowerFactorMeasure convertT7(uint32_t n);
    /** Convert T16 encoding to Measure.*/
    Measure convertT16(uint32_t n);
    /** Convert T17 encoding to Measure.*/
    Measure convertT17(uint32_t n);
    /** Save the settings on the target device. */
    bool saveSettings(uint8_t address, uint8_t attempts = 3);
    /** Reset the settings on the target device. */
    bool resetSettings(uint8_t address, uint8_t attempts = 3);
    /** Restart the target device. */
    bool restartDevice(uint8_t address, uint8_t attempts = 3);

private:
    /**
     * @param mantissa As unsigned 32-bits integer.
     * @param exponent As unsigned 32-bits integer.
     *
     * @return Performs validation and returns a Measure.
     *
     * @warning The Measure contains an error code that indicates
     * the result of the validation.
     */
    Measure generateMeasure(uint32_t mantissa, uint32_t exponent);
};

#endif
