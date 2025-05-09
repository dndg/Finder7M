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
    // Active power
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

    // Reactive power
    Measure pr1 = f7m.getReactivePowerPhase1(MODBUS_7M_ADDRESS);
    Serial.print("Reactive power phase 1 | mantissa: ");
    Serial.print(pr1.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pr1.exponent());
    Serial.print(", float: ");
    Serial.println(pr1.toFloat());
    Measure pr2 = f7m.getReactivePowerPhase2(MODBUS_7M_ADDRESS);
    Serial.print("Reactive power phase 2 | mantissa: ");
    Serial.print(pr2.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pr2.exponent());
    Serial.print(", float: ");
    Serial.println(pr2.toFloat());
    Measure pr3 = f7m.getReactivePowerPhase3(MODBUS_7M_ADDRESS);
    Serial.print("Reactive power phase 3 | mantissa: ");
    Serial.print(pr3.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pr3.exponent());
    Serial.print(", float: ");
    Serial.println(pr3.toFloat());

    // Apparent power
    Measure pa1 = f7m.getApparentPowerPhase1(MODBUS_7M_ADDRESS);
    Serial.print("Apparent power phase 1 | mantissa: ");
    Serial.print(pa1.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pa1.exponent());
    Serial.print(", float: ");
    Serial.println(pa1.toFloat());
    Measure pa2 = f7m.getApparentPowerPhase2(MODBUS_7M_ADDRESS);
    Serial.print("Apparent power phase 2 | mantissa: ");
    Serial.print(pa2.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pa2.exponent());
    Serial.print(", float: ");
    Serial.println(pa2.toFloat());
    Measure pa3 = f7m.getApparentPowerPhase3(MODBUS_7M_ADDRESS);
    Serial.print("Apparent power phase 3 | mantissa: ");
    Serial.print(pa3.mantissa());
    Serial.print(", exponent: ");
    Serial.print(pa3.exponent());
    Serial.print(", float: ");
    Serial.println(pa3.toFloat());

    delay(2000);
}
