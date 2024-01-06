//
//    FILE: rotaryDecoder.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
//    DATE: 2021-05-08
// PURPOSE: rotary decoder library for Arduino
//     URL: https://github.com/RobTillaart/rotaryDecoder


#include "rotaryDecoder.h"


/////////////////////////////////////////////////////
//
//  CONSTRUCTORS
//
rotaryDecoder::rotaryDecoder(const int8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


bool rotaryDecoder::begin(uint8_t count)
{
  _count = count;
  if (_count > 4) _count = 4;

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
  uint8_t value = _read8();
  _lastValue = value;
  for (uint8_t i = 0; i < _count; i++)
  {
    _lastPos[i] = value & 0x03;
    value >>= 2;
  }
}


bool rotaryDecoder::checkChange()
{
  uint8_t value = _read8();
  return (_lastValue != value);
}


bool rotaryDecoder::update()
{
  uint8_t value = _read8();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 2)
  {
    uint8_t currentpos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  //  fall through..
      case 0b0111:
      case 0b1110:
      case 0b1000:
        _encoder[i]++;
        break;
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        _encoder[i]--;
        break;
    }
    _lastPos[i] = currentpos;
  }
  return true;
}


bool rotaryDecoder::updateSingle()
{
  uint8_t value = _read8();
  if (_lastValue == value)
  {
    return false;
  }

 _lastValue = value;
  for (uint8_t i = 0; i < _count; i++, value >>= 2)
  {
    uint8_t currentpos = (value & 0x03);
    uint8_t change = (_lastPos[i] << 2) | currentpos;
    switch (change)
    {
      case 0b0001:  //  fall through..
      case 0b0111:
      case 0b1110:
      case 0b1000:
        _encoder[i] += 1;
        break;
      case 0b0011:
      case 0b0110:
      case 0b1001:
      case 0b1100:
        _encoder[i] += 2;
        break;
      case 0b0010:
      case 0b0100:
      case 0b1101:
      case 0b1011:
        _encoder[i] += 3;
        break;
    }
    _lastPos[i] = currentpos;
  }
  return true;
}


int32_t rotaryDecoder::getValue(uint8_t re)
{
  return _encoder[re];
}


void rotaryDecoder::setValue(uint8_t re, int32_t value)
{
  _encoder[re] = value;
}


uint8_t rotaryDecoder::getLastPosition(uint8_t re)
{
  return _lastPos[re];
};

/////////////////////////////////////////////////////
//
//  PRIVATE
//
uint8_t rotaryDecoder::_read8()
{
  _wire->requestFrom(_address, (uint8_t)1);
  return _wire->read();
}


//  -- END OF FILE --

