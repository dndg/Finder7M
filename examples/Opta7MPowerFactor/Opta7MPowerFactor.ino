#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 1;

constexpr uint8_t REG_PF_T = 164;  // Power Factor Total
constexpr uint8_t REG_PF_L1 = 166; // Power Factor phase 1

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

    // Read some Measures and print them
    Measure inActive = f7m.getMIDInActiveEnergy(MODBUS_7M_ADDRESS);
    printMeasure("IN Active Energy", inActive);
    Measure frequency = f7m.getFrequency(MODBUS_7M_ADDRESS);
    printMeasure("Frequency", frequency);
    Measure voltage = f7m.getVoltage(MODBUS_7M_ADDRESS);
    printMeasure("Voltage", voltage);
    Measure pt = f7m.getActivePowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Active Power Total", pt);

    // Then read the Power Factor Total
    uint32_t pft = f7m.modbus7MRead32(MODBUS_7M_ADDRESS, REG_PF_T);
    PowerFactorMeasure powerFactorTotal = f7m.convertT7(pft);
    printPFMeasure("Power Factor Total", powerFactorTotal);

    // Then read the Power Factor L1
    uint32_t pfl1 = f7m.modbus7MRead32(MODBUS_7M_ADDRESS, REG_PF_L1);
    PowerFactorMeasure powerFactorL1 = f7m.convertT7(pfl1);
    printPFMeasure("Power Factor L1", powerFactorL1);
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

void printPFMeasure(String label, PowerFactorMeasure m)
{
    int32_t mantissa = m.mantissa();
    int32_t exponent = m.exponent();
    Serial.print("   " + label + " = ");
    if (!m.isReadError())
    {
        Serial.println("[ isImport=" + String(m.isImport() ? "true" : "false") +
                       ", isExport=" + String(m.isExport() ? "true" : "false") +
                       ", isInductive=" + String(m.isInductive() ? "true" : "false") +
                       ", isCapacitative=" + String(m.isCapacitative() ? "true" : "false") +
                       ", mantissa=" + String(mantissa) +
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
        case INVALID_IMPORT_BITMASK:
            Serial.println("error, read import/export bitmask is not 0x00 nor 0xFF!");
            break;
        case INVALID_INDUCTIVE_BITMASK:
            Serial.println("error, read inductive/capacitative bitmask is not 0x00 nor 0xFF!");
            break;
        }
    }
};
