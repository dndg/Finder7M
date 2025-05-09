#include <Finder7M.h>

Finder7M f7m;
constexpr uint8_t MODBUS_7M_ADDRESS = 1;

void setup()
{
    Serial.begin(38400);
    f7m.init();
}

void loop()
{
    Measure p1 = f7m.getActivePowerPhase1(MODBUS_7M_ADDRESS);
    Serial.print("Active power phase 1 | mantissa: ");
    Serial.print(p1.mantissa());
    Serial.print(", exponent: ");
    Serial.print(p1.exponent());
    Serial.print(", float: ");
    Serial.println(p1.toFloat());

    Measure p2 = f7m.getActivePowerPhase2(MODBUS_7M_ADDRESS);
    Serial.print("Active power phase 2 | mantissa: ");
    Serial.print(p2.mantissa());
    Serial.print(", exponent: ");
    Serial.print(p2.exponent());
    Serial.print(", float: ");
    Serial.println(p2.toFloat());

    Measure p3 = f7m.getActivePowerPhase3(MODBUS_7M_ADDRESS);
    Serial.print("Active power phase 3 | mantissa: ");
    Serial.print(p3.mantissa());
    Serial.print(", exponent: ");
    Serial.print(p3.exponent());
    Serial.print(", float: ");
    Serial.println(p3.toFloat());

    delay(2000);
}
