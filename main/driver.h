#include <EEPROM.h>
class Driver
{
  public:
  Driver(int pin_a, int pin_b, int pin_c, int pin_d);
  int pin_a;
  int pin_b;
  int pin_c;
  int pin_d;
  int a;
  int b;
  int c;
  int d;
  int dir;
  void single_step();  
  void steps(int val);
  void load(int addr);
  void update_coils();
  int save(int addr);
  
};
