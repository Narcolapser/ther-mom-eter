#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

const char* MB = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/NV/nellis_AFB.json";
const char* TM = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/SD/Vermillion.json";
const char* BJ = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/decorah.json";
const char* NA = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/humboldt.json";
const char* EG = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/west_Des_Moines.json";
const char* KA = "http://api.wunderground.com/api/b3d8129648ddfcc6/conditions/q/IA/pella.json";

ESP8266WiFiMulti WiFiMulti;

void setup_web()
{
  WiFiMulti.addAP("ArchNet", "nospacesorcaps");
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
