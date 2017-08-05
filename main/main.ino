#include <EEPROM.h>
//#include "driver.h"
#include "web.h"
#include "dial.h"

Dial dialKA(16,0,5,4,50,P_LOCAL);
Dial dialEG(15,13,12,14,50,P_LOCAL);
Dial dialNA(5,4,3,2,50,P_REMOTE);
Dial dialBJ(14,15,16,17,50,P_REMOTE);
Dial dialTM(10,11,12,13,50,P_REMOTE);
Dial dialMB(9,8,7,6,50,P_REMOTE);

byte x = 0;
int val = 0;
int steps = 0;
int update_delay = 5000;
int last_update = millis();

void handleStatus(){
  String message = "Ther-MOM-eter status. here is where I currently think I'm pointing:\n\n";
  message += "\tKennan and Alaina: ";
  message += dialKA.temp;
  message += "\n\tEthan and Gina: ";
  message +=  dialEG.temp;
  message += "\n\tNatalia: ";
  message +=  dialNA.temp;
  message += "\n\tBrady and Julie: ";
  message +=  dialBJ.temp;
  message += "\n\tToby and Megan: ";
  message +=  dialTM.temp;
  message += "\n\tMicah and Becca: ";
  message +=  dialMB.temp;
  server.send( 200, "text/plain", message);
}

void handleKA() {
  String message = "Kennan and Alaina updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialKA.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void handleEG() {
  String message = "Ethan and Gina updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialEG.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void handleNA() {
  String message = "Natalia updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialNA.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void handleBJ() {
  String message = "Brady and Julie updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialBJ.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void handleTM() {
  String message = "Toby and Megan updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialTM.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void handleMB() {
  String message = "Micah and Becca updater.\n\n";
  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }
  dialMB.setTemp(atoi(server.arg(0).c_str()));
  server.send ( 200, "text/plain", message );
}

void setup() 
{
  Serial.begin(9800);
  EEPROM.begin(512);
  
  dialKA.load(0);
  dialEG.load(5);
  dialNA.load(10);
  dialBJ.load(15);
  dialTM.load(20);
  dialMB.load(25);

  setup_web();
  server.on("/status", handleStatus);
  server.on("/KA", handleKA);
  server.on("/EG", handleEG);
  server.on("/NA", handleNA);
  server.on("/BJ", handleBJ);
  server.on("/TM", handleTM);
  server.on("/MB", handleMB);
  
  randomSeed(analogRead(0));

  Serial.println("Setup is done.");

}

void loop() 
{
  val = random(20);
  dialKA.newTemp(val);
  dialEG.newTemp(val);
  dialNA.newTemp(val);
  dialBJ.newTemp(val);
  dialTM.newTemp(val);
  dialMB.newTemp(val);
  
  dialKA.save(0);
  dialEG.save(5);
  dialNA.save(10);
  dialBJ.save(15);
  dialTM.save(20);
  dialMB.save(25);
  
  last_update = millis();
  while (millis() - last_update < update_delay)
    server.handleClient();

}
