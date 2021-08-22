#include "ESP8266WiFi.h"

const char* ssid = "********";
const char* pswd = "********";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Setting up WiFi...");
  WiFi.begin(ssid, pswd);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connection successful");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP()); 
}

void loop() {

}
