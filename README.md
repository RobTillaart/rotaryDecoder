
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
- **void readInitialState()** read the inital state of the 4 rotary encoders
- **bool checkChange()** polling to see if one or more RE have changed
- **void update()** update the internal counters of the RE.
- **uint32_t getValue(uint8_r re)** returns the RE counter.
- **void setValue(uint8_r re, uint32_t val = 0)** set the internal counter to val, default 0


## Debugging

- **uint32_t getLastPosition(uint8_r re)**

## Operational

See examples..

