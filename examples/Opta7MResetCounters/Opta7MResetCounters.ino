#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 20;

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
    Serial.println(f7m.resetCounters(MODBUS_7M_ADDRESS) ? "Reset counters" : "Error! Could not reset counters");
}
