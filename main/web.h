#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include "Arduino.h"

ESP8266WebServer server(80);


const char* MB_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/NV/nellis_AFB.json";
const char* TM_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/SD/Vermillion.json";
const char* BJ_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/decorah.json";
const char* NA_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/humboldt.json";
const char* EG_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/west_Des_Moines.json";
const char* KA_url = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/pella.json";

ESP8266WiFiMulti WiFiMulti;


void handleRoot() {
  server.send(200, "text/plain", "hello from ther-mom-eter!");
}

//void handleMB() {
//  String message = "Micah and Becca handler.\n\n";
//  message += "URI: ";
//  message += server.uri();
//  message += "\nMethod: ";
//  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
//  message += "\nArguments: ";
//  message += server.args();
//  message += "\n";
//
//  for ( uint8_t i = 0; i < server.args(); i++ ) {
//    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
//  }
//
//  server.send ( 404, "text/plain", message );
//}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup_web()
{
  Serial.print("setting up web stuff.");
  WiFiMulti.addAP("ArchNet", "nospacesorcaps");
  WiFi.begin("ArchNet", "nospacesorcaps");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);


//  server.on("/MB", handleMB);
   

  server.onNotFound(handleNotFound);

  server.begin();
}

String getPayload(const char* loc)
{
  HTTPClient http;
  http.begin(loc);
  int httpCode = http.GET();
  String payload = "";
  if(httpCode > 0) 
  {
    // HTTP header has been send and Server response header has been handled
    //Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    
    // file found at server
    if(httpCode == HTTP_CODE_OK) 
    {
      payload = http.getString();
      //Serial.println(payload);
    }
  } 
  else
  {
    //Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    return "nope";
  }
    
  http.end();

  return payload;
}

float getTemp(const char* loc)
{
  String payload = getPayload(loc);
  int floc = payload.indexOf("temp_f") + 8;
  String temp = payload.substring(floc,payload.indexOf(",",floc));
  return temp.toFloat();
}
