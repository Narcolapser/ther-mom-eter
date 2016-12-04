#include "driver.h"
#include <EEPROM.h>
#include "Arduino.h"

class Dial
{
  public:
    int temp;
    Driver *driver;
    Dial(int pin_a, int pin_b, int pin_c, int pin_d, int temp); 
    Dial(); 
    void save(int loc);
    void load(int loc);
    void setTemp(int temp);
    void newTemp(int temp);
    void calibrate(int adjustment);
};
