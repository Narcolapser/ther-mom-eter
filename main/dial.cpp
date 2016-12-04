#include "dial.h"


Dial::Dial(int pin_a, int pin_b, int pin_c, int pin_d, int temp)
{
  this->driver = new Driver(pin_a, pin_b, pin_c, pin_d);
  this->temp = temp;
}
void Dial::load(int loc)
{
  int val;
  EEPROM.get(loc, val);
  this->temp = val;
  val = this->temp;
  this->driver->load(loc + 5);
}
void Dial::save(int loc)
{
  EEPROM.put(loc,this->temp);
  this->driver->save(loc+5);
  EEPROM.commit();
}
void Dial::newTemp(int temp)
{
  this->driver->steps((temp - this->temp)*10);
  this->temp = temp;
}
void Dial::calibrate(int adjustment)
{
  this->driver->steps(adjustment);
}

