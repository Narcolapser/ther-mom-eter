#include <EEPROM.h>
//#include "driver.h"
#include "web.h"
#include "dial.h"

//Dial dial(15,13,12,14,30);
Dial dialMB(2,0,5,16,50);
byte x = 0;
int val = 0;
int steps = 0;

void setup() 
{
  dialMB.save(0);
  Serial.begin(9800);
  Serial.println("Setup begun.");
  Serial.println("Temp:");
  Serial.println(String(dialMB.temp));
  EEPROM.begin(512);
  //EEPROM.write(1,85);
  //EEPROM.write(1,0);
  //EEPROM.commit();
  Serial.println(dialMB.getSign(dialMB.temp));
  Serial.println(dialMB.getCen(dialMB.temp));
  Serial.println(dialMB.getDec(dialMB.temp));
  Serial.println(dialMB.getMono(dialMB.temp));
  dialMB.load(0);
  Serial.println("Reading EEPROM:");
  Serial.println(EEPROM.read(0));
  Serial.println(EEPROM.read(1));
  Serial.println(EEPROM.read(2));
  Serial.println(EEPROM.read(3));
  Serial.println(EEPROM.read(4));
  Serial.println(EEPROM.read(5));
  Serial.println("Motor pins:");
  Serial.println(dialMB.driver->pin_a);
  Serial.println(dialMB.driver->pin_b);
  Serial.println(dialMB.driver->pin_c);
  Serial.println(dialMB.driver->pin_d);
  Serial.println("Temp:");
  Serial.println(dialMB.temp);
  setup_web();
  randomSeed(analogRead(0));
  pinMode(4, INPUT);
  delay(100);
  while(digitalRead(4))
  {
    Serial.println("Calibrating up 1 degree");
    dialMB.calibrate(10);
    delay(500);
  }
  Serial.println("Setup is done.");
//  Serial.println(getTemp(MB));
//  Serial.println(getTemp(TM));
//  Serial.println(getTemp(BJ));
//  Serial.println(getTemp(NA));
//  Serial.println(getTemp(EG));
//  Serial.println(getTemp(KA));
}

void loop() 
{
  delay(2000);
  val = random(140)-40;
  Serial.print("Temp was: ");
  Serial.print(dialMB.temp);
  Serial.print(" am now setting it to: ");
  Serial.print(val);
  Serial.print(" moving by: ");
  Serial.println((val - dialMB.temp)*10);
  dialMB.newTemp(val);
  dialMB.save(0);
  delay(3000);
//  if(digitalRead(4))
//  {
//    Serial.println(++steps);
//    dialMB.calibrate(1);
//  }
//  delay(50);
}
