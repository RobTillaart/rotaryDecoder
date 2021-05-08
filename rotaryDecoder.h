#pragma once
//
//    FILE: rotaryDecoder.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-08
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoder


#include "Arduino.h"
#include "Wire.h"

#define ROTARY_DECODER_LIB_VERSION         (F("0.1.0"))


class rotaryDecoder
{
public:
  explicit rotaryDecoder(const int8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool begin(uint8_t sda, uint8_t scl, uint8_t cnt = 4);
#endif

  bool begin(uint8_t cnt = 4);
  bool isConnected();

  void readInitialState();

  // polling version
  bool checkChange();
  void update();

  uint32_t getValue(uint8_t re) { return _RE[re]; };
  void     setValue(uint8_t re, uint32_t val = 0) { _RE[re] = val; };

  // DEBUG
  uint32_t getLastPosition(uint8_t re) { return _lastPos[re]; };

private:
  uint8_t   _cnt = 0;
  uint8_t   _lastPos[4] = { 0,0,0,0 };
  uint32_t  _RE[4] = { 0,0,0,0 };

  uint8_t   _read8();
  uint8_t   _address;
  TwoWire * _wire;
};

// -- END OF FILE --
