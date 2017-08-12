#include "dial.h"

Dial::Dial(int pin_a, int pin_b, int pin_c, int pin_d, int temp,pin_t loc)
{
  this->driver = new Driver(pin_a, pin_b, pin_c, pin_d, loc);
  this->temp = temp;
  this->step_factor = 11;
}
void Dial::load(int loc)
{
  char sign = EEPROM.read(loc + 0);
  char cen =  EEPROM.read(loc + 1);
  char dec =  EEPROM.read(loc + 2);
  char mono = EEPROM.read(loc + 3);
  int val = charValue(sign, cen, dec, mono);
  this->temp = val;
  val = this->temp;
  this->driver->load(loc + 5);
}
void Dial::save(int loc)
{
  //EEPROM.put(loc,this->temp);
  EEPROM.write(loc + 0, getSign(this->temp));
  EEPROM.write(loc + 1, getCen(this->temp));
  EEPROM.write(loc + 2, getDec(this->temp));
  EEPROM.write(loc + 3, getMono(this->temp));
  this->driver->save(loc+4);
  EEPROM.commit();
}
void Dial::newTemp(int temp)
{
  int dist = (temp - this->temp) % 140;
  this->driver->steps(dist*this->step_factor);
  this->temp = temp;
  this->driver->off();
}
void Dial::setTemp(int temp)
{
  Serial.print("Setting temp to:");
  Serial.println(temp);
  int temptemp = this->temp;
  this->temp = temp;
  this->newTemp(temptemp);
}
void Dial::calibrate(int adjustment)
{
  this->driver->steps(adjustment);
}
float Dial::charValue(char sign, char cen, char dec, char mono)
{
  float val = 0;
  val += (mono - '0') * 1;
  val += (dec - '0') * 10;
  val += (cen - '0') * 100;
  if (sign == '-')
    val *= -1;
  return val;
}

char Dial::getSign(int val)
{
  if (val >= 0)
    return '+';
  return '-';
}
char Dial::getCen(int val)
{
  if (val >= 100)
    return '1';
  return '0';
}
char Dial::getDec(int val)
{
  val /= 10;
  val %= 10;
  if (val < 0)
    val *= -1;
  return '0'+val;
   
}
char Dial::getMono(int val)
{
  val %= 10;
  if (val < 0)
    val *= -1;
  return '0'+val;
}
