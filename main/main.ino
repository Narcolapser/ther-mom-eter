#include <EEPROM.h>
#include "driver.h"

Driver driver(15,13,12, 14);

void setup() 
{
  Serial.begin(9800);
  Serial.println("Setup is done.");
  EEPROM.begin(512);
  //EEPROM.write(1,85);
  EEPROM.write(1,0);
  EEPROM.commit();
  pinMode(15, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  Serial.println(EEPROM.read(1));
  driver.load(1);
}

void loop() 
{
  Serial.println("LOOP!");

  //Serial.print((driver.a || driver.b || driver.c || driver.d));
  Serial.print(driver.a);
  Serial.print(driver.b);
  Serial.print(driver.c);
  Serial.println(driver.d);
  //Serial.println(driver.dir);
  //Serial.println(driver.save(1));
  
  delay(1000);
  driver.steps(1024);
}
