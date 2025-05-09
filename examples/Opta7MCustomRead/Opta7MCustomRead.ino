#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 1;
constexpr uint8_t REG_ENERGY_C1 = 414;
constexpr uint8_t REG_ENERGY_C1_EXPONENT = 446;

void setup()
{
    Serial.begin(38400);

    if (!f7m.init(38400, SERIAL_8N1, 500))
    {
        while (1)
        {
        }
    }
}

void loop()
{
    uint32_t m = f7m.modbus7MRead32(MODBUS_7M_ADDRESS, REG_ENERGY_C1, 1);
    uint32_t e = f7m.modbus7MRead16(MODBUS_7M_ADDRESS, REG_ENERGY_C1_EXPONENT, 1);
    if (m != INVALID_DATA && e != INVALID_DATA)
    {
        Serial.println("Counter C1 mantissa = " + String(m));
        Serial.println("Counter C1 exponent = " + String(e));
    }
    else
    {
        Serial.println("Read failed!");
    }

    Measure mid = f7m.getMIDInActiveEnergy(MODBUS_7M_ADDRESS, 1);
    if (!mid.isReadError())
    {
        Serial.println("Mid 1 = " + String(mid.toFloat()));
    }
    else
    {
        Serial.println("Read failed!");
    }
}
