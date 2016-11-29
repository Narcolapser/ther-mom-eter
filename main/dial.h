#include "driver.h"

class Dial
{
  public:
    int temp;
    Driver *driver;
    Dial(int pin_a, int pin_b, int pin_c, int pin_d, int temp); 
    Dial(int loc);
};
