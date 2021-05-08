
[![Arduino CI](https://github.com/RobTillaart/rotaryDecoder/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/rotaryDecoder/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/rotaryDecoder.svg?maxAge=3600)](https://github.com/RobTillaart/rotaryDecoder/releases)


# rotaryDecoder

Arduino library for a PCF8574 based rotary decoder - supports 4 RE.


## Description

Experimental - not tested yet

## interface

- **rotaryDecoder(const int8_t address, TwoWire \*wire = Wire);**
- **bool begin(uint8_t sda, uint8_t scl, uint8_t cnt = 4)** ESP32 ea initializes the class
returns true if the PCF8574 is on the I2C bus.
- **bool begin(uint8_t cnt = 4)** UNO ea. initializes the class
returns true if the PCF8574 is on the I2C bus.
- **bool isConnected()** returns true if the PCF8574 is on the I2C bus.

## Core functions

- **void readInitialState()** read the inital state of the 4 rotary encoders
- **bool checkChange()** polling to see if one or more RE have changed
- **void update()** update the internal counters of the RE. These will add +1 or -1 depending on direction. 
- **void updateSingle()** update the internal counters of the RE. This will add +1 +2 or +3 as it assumes that the rotary encoder only goes into a single direction. 

## Counters

- **uint32_t getValue(uint8_r re)** returns the RE counter.
- **void setValue(uint8_r re, uint32_t val = 0)** set the internal counter to val, default 0


## Debugging

- **int8_t getLastPosition(uint8_r re)**


## Performance

As the decoder is based upon a PCF8574, a I2C device, the performance is affected by the 
clockspeed of the I2C bus. All three core functions have one call to **\_read()** which is the most expensive part.

Early tests gave the following times (Arduino UNO) for the **update()** 
function (with no updates it is ~8 us faster). Note that above 400KHz the gain becomes less.

| I2C speed | time (us) | delta |
|:---------:|:---------:|:-----:|
| 100 KHz   |    247    |       |
| 200 KHz   |    146    |  99   |
| 300 KHz   |    110    |  36   |
| 400 KHz   |     95    |  15   | preferred max
| 500 KHz   |     84    |  11   |
| 600 KHz   |     79    |   5   |
| 700 KHz   |     73    |   6   |

At @400KHz it can update 4 rotary encoders in ~100us. 
At a 50% update percentage this implies a max of about 
5000 **update()** calls per second.

Note that a high speed drill goes up to 30000 RPM = 500 RPS = 2000 interrupts per second, assuming 4 pulses = 360°. (not tested)

## Operational

See examples..

