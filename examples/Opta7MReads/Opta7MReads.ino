#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 1;

void setup()
{
    Serial.begin(38400);

    if (!f7m.init())
    {
        while (1)
        {
        }
    }
}

void loop()
{
    delay(3000);

    Serial.println("** Reading 7M at address " + String(MODBUS_7M_ADDRESS));

    // Model Number
    Finder7MModelNumber modelBuffer;
    Serial.print("   Serial Model = ");
    if (f7m.getModelNumber(MODBUS_7M_ADDRESS, modelBuffer))
    {
        Serial.println(String(modelBuffer, 16));
    }
    else
    {
        Serial.println("read error!");
    }

    // Serial Number
    Finder7MSerialNumber serialBuffer;
    Serial.print("   Serial Number = ");
    if (f7m.getSerialNumber(MODBUS_7M_ADDRESS, serialBuffer))
    {
        Serial.println(String(serialBuffer, 8));
    }
    else
    {
        Serial.println("read error!");
    }

    // Software and hardware reference
    uint16_t sref = f7m.getSoftwareReference(MODBUS_7M_ADDRESS);
    printUint("Software Reference", sref);
    uint16_t href = f7m.getHardwareReference(MODBUS_7M_ADDRESS);
    printUint("Hardware Reference", href);

    // MID counters
    Measure inActive = f7m.getMIDInActiveEnergy(MODBUS_7M_ADDRESS);
    printMeasure("IN Active Energy", inActive);
    Measure exActive = f7m.getMIDExActiveEnergy(MODBUS_7M_ADDRESS);
    printMeasure("EX Active Energy", exActive);
    Measure inReactive = f7m.getMIDInReactiveEnergy(MODBUS_7M_ADDRESS);
    printMeasure("IN Reactive Energy", inReactive);
    Measure exReactive = f7m.getMIDExReactiveEnergy(MODBUS_7M_ADDRESS);
    printMeasure("EX Reactive Energy", exReactive);

    // MID counters x1000
    Measure inActiveXK = f7m.getMIDInActiveEnergyXK(MODBUS_7M_ADDRESS);
    printMeasure("IN Active Energy x1000", inActiveXK);
    Measure exActiveXK = f7m.getMIDExActiveEnergyXK(MODBUS_7M_ADDRESS);
    printMeasure("EX Active Energy x1000", exActiveXK);
    Measure inReactiveXK = f7m.getMIDInReactiveEnergyXK(MODBUS_7M_ADDRESS);
    printMeasure("IN Reactive Energy x1000", inReactiveXK);
    Measure exReactiveXK = f7m.getMIDExReactiveEnergyXK(MODBUS_7M_ADDRESS);
    printMeasure("EX Reactive Energy x1000", exReactiveXK);

    // Current
    Measure current1 = f7m.getCurrentPhase1(MODBUS_7M_ADDRESS);
    printMeasure("Current Phase 1", current1);
    Measure current2 = f7m.getCurrentPhase2(MODBUS_7M_ADDRESS);
    printMeasure("Current Phase 2", current2);
    Measure current3 = f7m.getCurrentPhase3(MODBUS_7M_ADDRESS);
    printMeasure("Current Phase 3", current3);

    // Voltage
    Measure voltage1 = f7m.getVoltagePhase1(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 1", voltage1);
    Measure voltage2 = f7m.getVoltagePhase2(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 2", voltage2);
    Measure voltage3 = f7m.getVoltagePhase3(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 3", voltage3);
    Measure voltage12 = f7m.getVoltagePhase12(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 1-2", voltage12);
    Measure voltage23 = f7m.getVoltagePhase23(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 2-3", voltage23);
    Measure voltage31 = f7m.getVoltagePhase31(MODBUS_7M_ADDRESS);
    printMeasure("Voltage Phase 3-1", voltage31);
    Measure angleVoltage12 = f7m.getPhaseAngleVoltage12(MODBUS_7M_ADDRESS);
    printMeasure("Phase angle voltage Phase 1-2", angleVoltage12);
    Measure angleVoltage23 = f7m.getPhaseAngleVoltage23(MODBUS_7M_ADDRESS);
    printMeasure("Phase angle voltage Phase 2-3", angleVoltage23);
    Measure angleVoltage31 = f7m.getPhaseAngleVoltage31(MODBUS_7M_ADDRESS);
    printMeasure("Phase angle voltage Phase 3-1", angleVoltage31);

    // Measurements
    Measure frequency = f7m.getFrequency(MODBUS_7M_ADDRESS);
    printMeasure("Frequency", frequency);
    Measure pt = f7m.getActivePowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Active Power Total", pt);
    Measure qt = f7m.getReactivePowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Reactive Power Total", qt);
    Measure st = f7m.getApparentPowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Apparent Power Total", st);
    Measure runTime = f7m.getRunTime(MODBUS_7M_ADDRESS);
    printMeasure("Run Time", runTime);

    // Configurable counters.
    Measure c1 = f7m.getEnergyCounterC1(MODBUS_7M_ADDRESS);
    printMeasure("C1", c1);
    Measure c2 = f7m.getEnergyCounterC2(MODBUS_7M_ADDRESS);
    printMeasure("C2", c2);
    Measure c3 = f7m.getEnergyCounterC3(MODBUS_7M_ADDRESS);
    printMeasure("C3", c3);
    Measure c4 = f7m.getEnergyCounterC4(MODBUS_7M_ADDRESS);
    printMeasure("C4", c4);
    Measure c5 = f7m.getEnergyCounterC5(MODBUS_7M_ADDRESS);
    printMeasure("C5", c5);
    Measure c6 = f7m.getEnergyCounterC6(MODBUS_7M_ADDRESS);
    printMeasure("C6", c6);
    Measure c7 = f7m.getEnergyCounterC7(MODBUS_7M_ADDRESS);
    printMeasure("C7", c7);
    Measure c8 = f7m.getEnergyCounterC8(MODBUS_7M_ADDRESS);
    printMeasure("C8", c8);
    Measure c9 = f7m.getEnergyCounterC9(MODBUS_7M_ADDRESS);
    printMeasure("C9", c9);
    Measure c10 = f7m.getEnergyCounterC10(MODBUS_7M_ADDRESS);
    printMeasure("C10", c10);
    Measure c11 = f7m.getEnergyCounterC11(MODBUS_7M_ADDRESS);
    printMeasure("C11", c11);
    Measure c12 = f7m.getEnergyCounterC12(MODBUS_7M_ADDRESS);
    printMeasure("C12", c12);
    Measure c13 = f7m.getEnergyCounterC13(MODBUS_7M_ADDRESS);
    printMeasure("C13", c13);
    Measure c14 = f7m.getEnergyCounterC14(MODBUS_7M_ADDRESS);
    printMeasure("C14", c14);
    Measure c15 = f7m.getEnergyCounterC15(MODBUS_7M_ADDRESS);
    printMeasure("C15", c15);
    Measure c16 = f7m.getEnergyCounterC16(MODBUS_7M_ADDRESS);
    printMeasure("C16", c16);
}

void printMeasure(String label, Measure m)
{
    int32_t mantissa = m.mantissa();
    int32_t exponent = m.exponent();
    Serial.print("   " + label + " = ");
    if (!m.isReadError())
    {
        Serial.println("[ mantissa=" + String(mantissa) +
                       ", exponent=" + String(exponent) +
                       ", float=" + m.toFloat() +
                       " ]");
    }
    else
    {
        uint8_t err = m.getErrorCode();
        switch (err)
        {
        case INVALID_MANTISSA:
            Serial.println("error while reading mantissa!");
            break;
        case INVALID_EXPONENT:
            Serial.println("error while reading exponent!");
            break;
        case INVALID_READ:
            Serial.println("read error!");
            break;
        }
    }
};

void printUint(String label, uint16_t n)
{
    int32_t n32 = (int16_t)n;
    Serial.println("   " + label + " = " + (n32 != INVALID_DATA ? String(n) : String("read error!")));
};
