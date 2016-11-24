/*#include <EEPROM.h>
class Driver
{
  public:
  Driver(){};
  int a;
  int b;
  int c;
  int d;
  int dir;
  void step()
  {
    
  }
  void steps(int val)
  {
    
  }
  void load(int addr)
  {
    int val = EEPROM.read(addr);
    this->a = val % 2;
    this->b = (val/4) % 2;
    this->c = (val/8) % 2;
    this->d = (val/16) % 2;
    this->dir = (val/32) % 2;
    Serial.println(this->a,this->b,this->c,this->d,this->dir); 
  }
};*/
