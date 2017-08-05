#include <EEPROM.h>
#include "pin_t.h"

#ifndef DRIVER_H
#define DRIVER_H

class Driver
{
  public:
  Driver(int pin_a, int pin_b, int pin_c, int pin_d, pin_t loc);
  int pin_a;
  int pin_b;
  int pin_c;
  int pin_d;
  int a;
  int b;
  int c;
  int d;
  int dir;
  pin_t loc;
  void single_step();  
  void steps(int val);
  void load(int addr);
  void update_coils();
  int save(int addr);
  void off();
  void pinWrite(int pin,int state);
  
};

#endif
