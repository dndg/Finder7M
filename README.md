# Finder 7M for Finder Opta library

This library allows to easily read counters from Finder 7M devices connected via ModBus to a Finder Opta, providing a number of built-in functions that simplify the process of reading measurements from both Measurement Instruments Directive (MID) certified counters and custom-configured counters.

The library also includes functions to directly read registers via ModBus and perform conversions.

## Usage

The code below shows a basic example of how to use this library:

```cpp
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
    Measure inActive = f7m.getMIDInActiveEnergy(MODBUS_7M_ADDRESS);
    Serial.println(String(inActive.mantissa()));
    Serial.println(String(inActive.exponent()));
}
```

For more details take a look at [the example sketch](./examples/Opta7MReads/Opta7MReads.ino) provided with the library.

## Resources

* [Getting started with Opta](https://opta.findernet.com/en/tutorial/getting-started).
* [Finder 7M.38 user's manual](https://cdn.findernet.com/app/uploads/manual7M38_EN.pdf).
* [ModBus over Serial Line](https://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf).

## License

This library is released under the GNU Lesser General Public License license. For more details read [the full license](./LICENSE.txt).

## Contact

For communication reach out to iot@dndg.it.
