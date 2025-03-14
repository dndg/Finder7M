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

    // Read the Power Factor total
    PowerFactorMeasure powerFactorTotal = f7m.getPowerFactorTotal(MODBUS_7M_ADDRESS);
    printPFMeasure("Power Factor Total", powerFactorTotal);

    // Then read the Power Factor on the phases
    PowerFactorMeasure powerFactor1 = f7m.getPowerFactorPhase1(MODBUS_7M_ADDRESS);
    printPFMeasure("Power Factor Phase 1", powerFactor1);
    PowerFactorMeasure powerFactor2 = f7m.getPowerFactorPhase2(MODBUS_7M_ADDRESS);
    printPFMeasure("Power Factor Phase 2", powerFactor2);
    PowerFactorMeasure powerFactor3 = f7m.getPowerFactorPhase3(MODBUS_7M_ADDRESS);
    printPFMeasure("Power Factor Phase 3", powerFactor3);
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
