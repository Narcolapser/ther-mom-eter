#include <EEPROM.h>
//#include "driver.h"
#include "web.h"
#include "dial.h"

Dial dialNA(15,13,12,14,30);
Dial dialMB(2,0,5,16,50);
byte x = 0;
int val = 0;
int steps = 0;
int update_delay = 5000;
int last_update = millis();

void handleMB() {
  String message = "Micah and Becca handler.\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  dialMB.setTemp(atoi(server.arg(0).c_str()));

  server.send ( 200, "text/plain", message );
}

void handleNA() {
  String message = "Natalia handler.\n\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  dialNA.setTemp(atoi(server.arg(0).c_str()));

  server.send ( 200, "text/plain", message );
}


void setup() 
{
  Serial.begin(9800);
  EEPROM.begin(512);
  
  dialMB.load(0);
  dialNA.load(10);

  setup_web();
  server.on("/MB", handleMB);
  server.on("/NA", handleNA);
  randomSeed(analogRead(0));

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
  val = random(140)-20;
  Serial.print("Temp was: ");
  Serial.print(dialMB.temp);
  Serial.print(" am now setting it to: ");
  Serial.print(val);
  Serial.print(" moving by: ");
  Serial.println((val - dialMB.temp)*10);
  dialMB.newTemp(val);
  dialMB.save(0);
  dialNA.newTemp(val);
  dialNA.save(10);
  last_update = millis();
  while (millis() - last_update < update_delay)
    server.handleClient();

}
