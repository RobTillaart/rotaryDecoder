//
//    FILE: rotaryDecoder.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2021-05-08
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoder
//
//  HISTORY:
//  0.1.0   2021-05-08  initial version
//


#include "rotaryDecoder.h"


/////////////////////////////////////////////////////
//
// CONSTRUCTORS
//
rotaryDecoder::rotaryDecoder(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool rotaryDecoder::begin(uint8_t sda, uint8_t scl, uint8_t cnt)
{
  _cnt = cnt;
  _wire = &Wire;
  _wire->begin(sda, scl);
  if (! isConnected()) return false;
  return true;
}
#endif


bool rotaryDecoder::begin(uint8_t cnt)
{
  _cnt = cnt;
  _wire->begin();
  if (! isConnected()) return false;
  return true;
}


bool rotaryDecoder::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


void rotaryDecoder::readInitialState()
{
  uint8_t val = _read8();
  for (uint8_t i = 0; i < _cnt; i++)
  {
    _lastPos[i] = val & 0x03;
    val >>= 2;
  }
}


bool rotaryDecoder::checkChange()
{
  uint8_t val = _read8();
  for (uint8_t i = 0; i < _cnt; i++, val >>= 2)
  {
    if (_lastPos[i] != (val & 0x03)) return true;
  }
  return false;
}


void rotaryDecoder::update()
{
  uint8_t val = _read8();

  for (uint8_t i = 0; i < _cnt; i++, val >>= 2)
  {
    uint8_t currentpos = (val & 0x03);
    if (_lastPos[i] != currentpos)        // moved!
    {
      uint8_t change = (_lastPos[i] << 2) | currentpos;
      switch (change)
      {
        case 0b0001:  // fall through..
        case 0b0111:
        case 0b1110:
        case 0b1000:
          _RE[i]++;
          break;
        case 0b0010:
        case 0b0100:
        case 0b1101:
        case 0b1011:
          _RE[i]--;
          break;
      }
      _lastPos[i] = currentpos;
    }
  }
}


uint8_t rotaryDecoder::_read8()
{
  // todo error handling;
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


// -- END OF FILE --
