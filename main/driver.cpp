#include <EEPROM.h>
#include "driver.h"
#include "Arduino.h"

Driver::Driver(int pin_a, int pin_b, int pin_c, int pin_d)
{
  this->a = 0;
  this->b = 0;
  this->c = 0;
  this->d = 0;
  this->pin_a = pin_a;
  this->pin_b = pin_b;
  this->pin_c = pin_c;
  this->pin_d = pin_d;
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
  EEPROM.commit();
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
    digitalWrite(this->pin_a,HIGH);
  else
    digitalWrite(this->pin_a,LOW);
  if(this->b)
    digitalWrite(this->pin_b,HIGH);
  else
    digitalWrite(this->pin_b,LOW);
  if(this->c)
    digitalWrite(this->pin_c,HIGH);
  else
    digitalWrite(this->pin_c,LOW);
  if(this->d)
    digitalWrite(this->pin_d,HIGH);
  else
    digitalWrite(this->pin_d,LOW);
  
  delay(5);
}
void Driver::steps(int val)
{
  while(val --> 0)
    this->single_step();
}

void Driver::off()
{
  digitalWrite(this->pin_a,LOW);
  digitalWrite(this->pin_b,LOW);
  digitalWrite(this->pin_c,LOW);
  digitalWrite(this->pin_d,LOW);
}
