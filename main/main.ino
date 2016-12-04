#include <EEPROM.h>
//#include "driver.h"
#include "web.h"
#include "dial.h"

//Dial dial(15,13,12,14,30);
Dial dial(2,0,5,16,30);
byte x = 0;
int val = 0;

void setup() 
{
  Serial.begin(9800);
  Serial.println("Setup begun.");
  EEPROM.begin(512);
  //EEPROM.write(1,85);
  EEPROM.write(1,0);
  EEPROM.commit();
  //dial.load(0);
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(4));
  Serial.println(EEPROM.read(5));
  Serial.println("Motor pins:");
  Serial.println(dial.driver->pin_a);
  Serial.println(dial.driver->pin_b);
  Serial.println(dial.driver->pin_c);
  Serial.println(dial.driver->pin_d);
  setup_web();
  randomSeed(analogRead(0));
  pinMode(4, INPUT);
  delay(100);
  while(digitalRead(4))
  {
    Serial.println("Calibrating up 1 degree");
    dial.calibrate(10);
    delay(500);
  }
  Serial.println("Setup is done.");
}

void loop() 
{
  val = random(140)-40;
  Serial.print("Temp was: ");
  Serial.print(dial.temp);
  Serial.print(" am now setting it to: ");
  Serial.print(val);
  Serial.print(" moving by: ");
  Serial.println((val - dial.temp)*10);
  dial.newTemp(val);
  dial.save(0);
  delay(5000);
}
