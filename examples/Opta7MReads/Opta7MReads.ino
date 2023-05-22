#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 2;

void setup()
{
    Serial.begin(9600);

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

    // Serial Number
    Finder7MSerialNumber buffer;
    Serial.print("   Serial Number = ");
    if (f7m.getSerialNumber(MODBUS_7M_ADDRESS, buffer))
    {
        Serial.println(String(buffer, 8));
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

    // Measurements
    Measure frequency = f7m.getFrequency(MODBUS_7M_ADDRESS);
    printMeasure("Frequency", frequency);
    Measure voltage = f7m.getVoltage(MODBUS_7M_ADDRESS);
    printMeasure("Voltage", voltage);
    Measure pt = f7m.getActivePowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Active Power Total", frequency);
    Measure qt = f7m.getReactivePowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Reactive Power Total", qt);
    Measure st = f7m.getApparentPowerTotal(MODBUS_7M_ADDRESS);
    printMeasure("Apparent Power Total", st);
    Measure runTime = f7m.getRunTime(MODBUS_7M_ADDRESS);
    printMeasure("Run Time", runTime);
}

void printMeasure(String label, Measure m)
{
    int32_t mantissa = m.mantissa();
    int32_t exponent = m.exponent();
    Serial.print("   " + label + " = ");
    if (mantissa != INVALID_DATA || exponent != INVALID_DATA)
    {
        Serial.println("[ mantissa=" + String(mantissa) +
                       ", exponent=" + String(exponent) +
                       ", float=" + m.toFloat() +
                       " ]");
    }
    else
    {
        Serial.println("read error!");
    }
};

void printUint(String label, uint16_t n)
{
    Serial.println("   " + label + " = " + (n != INVALID_DATA ? String(n) : String("read error!")));
};
