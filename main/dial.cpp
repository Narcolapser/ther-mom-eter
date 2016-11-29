#include "dial.h"
#include <EEPROM.h>
#include "Arduino.h"

Dial::Dial(int pin_a, int pin_b, int pin_c, int pin_d, int temp)
{
  this->driver = new Driver(pin_a, pin_b, pin_c, pin_d);
  this->temp = temp;
}
//Dial::Dial(int loc);

