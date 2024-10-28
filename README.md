# Finder 7M for Finder Opta library

This library allows to easily read counters from Finder 7M devices connected
via ModBus to a Finder Opta, providing a number of built-in functions that
simplify the process of reading measurements from both Measurement Instruments
Directive (MID) certified counters and custom-configured counters.

The library also includes functions to directly read registers via ModBus and
perform conversions. Additionally, using this library it is possible to reset
the counters of the Finder 7M.

## Usage

The code below shows a basic example of how to use this library:

```cpp
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
    Measure inActive = f7m.getMIDInActiveEnergy(MODBUS_7M_ADDRESS);
    Serial.println(String(inActive.mantissa()));
    Serial.println(String(inActive.exponent()));
}
```

For more details take a look at [the example
sketch](./examples/Opta7MReads/Opta7MReads.ino) provided with the library.

### Notes

When using this library keep in mind that:

* The default baudrate is `38400`.
* The default configuration is `8-N-1`.
* When writing to registers you should always write one register at a time.

## Resources

* [Getting started with
  Opta](https://opta.findernet.com/en/tutorial/getting-started).
* [Finder 7M.38 user's
  manual](https://cdn.findernet.com/app/uploads/manual7M38_EN.pdf).
* [ModBus over Serial
  Line](https://www.modbus.org/docs/Modbus_over_serial_line_V1_02.pdf).

## License

This library is released under the GNU Lesser General Public License license.
For more details read [the full license](./LICENSE.txt).

## Contact

For communication reach out to <iot@dndg.it>.
