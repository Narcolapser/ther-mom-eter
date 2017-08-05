#include <EEPROM.h>
#include "driver.h"
#include "Arduino.h"

Driver::Driver(int pin_a, int pin_b, int pin_c, int pin_d, pin_t loc)
{
  this->a = 0;
  this->b = 0;
  this->c = 0;
  this->d = 0;
  this->pin_a = pin_a;
  this->pin_b = pin_b;
  this->pin_c = pin_c;
  this->pin_d = pin_d;
  this->loc = loc;

  if (loc == P_LOCAL)
  {
    pinMode(pin_a, OUTPUT);
    pinMode(pin_b, OUTPUT);
    pinMode(pin_c, OUTPUT);
    pinMode(pin_d, OUTPUT);
  }
  
  this->dir = 0;
};

void Driver::load(int addr)
{
  int val = EEPROM.read(addr);
  this->a = val % 2;
  this->b = (val/2) % 2;
  this->c = (val/4) % 2;
  this->d = (val/8) % 2;
  this->dir = (val/16) % 2;
//  Serial.println(this->a,this->b,this->c,this->d,this->dir);   
}
int Driver::save(int addr)
{
  int val = (16 * this->dir) + 
      (8 * this->d) + 
      (4 * this->c) + 
      (2 * this->b) + 
      this->a;
  EEPROM.write(addr,val);
  return val;
}

void Driver::single_step()
{
  //Check to see if anything has been done yet:
  if ((this->a || this->b || this->c || this->d)== 0)
  {
    //set the starting state:
    this->a = 1;
    this->b = 1;
  }
  if (this->dir)
  {
    if (this->a)
    {
      if (this->b)
      {
        this->a = 0;
        this->c = 1;
      }
      else
      {
        this->d = 0;
        this->b = 1;
      }
    }
    else
    {
      if (this->b)
      {
        this->b = 0;
        this->d = 1;
      }
      else
      {
        this->c = 0;
        this->a = 1;
      }
    }
  }
  else
  {
    if (this->a)
    {
      if (this->b)
      {
        this->d = 1;
        this->b = 0;
      }
      else
      {
        this->a = 0;
        this->c = 1;
      }
    }
    else
    {
      if (this->b)
      {
        this->c = 0;
        this->a = 1;
      }
      else
      {
        this->b = 1;
        this->d = 0;
      }
    }
  }
  this->update_coils();
}
void Driver::update_coils()
{
  if(this->a)
    this->pinWrite(this->pin_a,HIGH);
  else
    this->pinWrite(this->pin_a,LOW);
  if(this->b)
    this->pinWrite(this->pin_b,HIGH);
  else
    this->pinWrite(this->pin_b,LOW);
  if(this->c)
    this->pinWrite(this->pin_c,HIGH);
  else
    this->pinWrite(this->pin_c,LOW);
  if(this->d)
    this->pinWrite(this->pin_d,HIGH);
  else
    this->pinWrite(this->pin_d,LOW);
  
  delay(5);
}
void Driver::steps(int val)
{
  if (val < 0)
  {
    this->dir = 1;
    val *= -1;
  }
  else
    this->dir = 0;
  while(val --> 0)
    this->single_step();
}

void Driver::off()
{
  this->pinWrite(this->pin_a,LOW);
  this->pinWrite(this->pin_b,LOW);
  this->pinWrite(this->pin_c,LOW);
  this->pinWrite(this->pin_d,LOW);
}

void Driver::pinWrite(int pin, int state)
{
  if(this->loc == P_LOCAL)
    digitalWrite(pin,state);
  else
  {
    if (state == HIGH)
      pin += 100;
    Serial.println(pin);
  }
  
}

