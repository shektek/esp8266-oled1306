#include <U8g2lib.h>
#include "ESP8266WiFi.h"

/* https://github.com/olikraus/u8g2 */
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, 16, 5, 4);

u8g2_uint_t offset;
u8g2_uint_t width;
char ipStr[20] = "IP: 0.0.0.0\0";
const char* ssid = "********";
const char* pwd = "********";
int status = WL_IDLE_STATUS;
int lastStatus = WL_IDLE_STATUS;
char message[256] = {0};

/* https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi */
WiFiServer server(503);

void setup() 
{
  Serial.begin(115200);  
  u8g2.begin();

  WiFi.begin(ssid, pwd);
}

void loop() 
{
  status = WiFi.status();
  if(status != lastStatus)
  {
    if(status == WL_CONNECTED)
    {
      server.begin();
      Serial.println("server started on port 503");
      memcpy(&ipStr[4], WiFi.localIP().toString().c_str(), strlen(WiFi.localIP().toString().c_str()));
    }
    else
    {
      memcpy(&ipStr[4], "Disconnected\0", 13);
    }
  
    lastStatus = WiFi.status();
  }

  WiFiClient client = server.available();
  if(client == true)
  {
    bool messageStart = false;
    bool keepReading = true;
    int i = 0;

    while(client.connected() && keepReading)
    {
      if(client.available())
      {
        String line = client.readStringUntil(0);
        Serial.println(line);
        if(line[0] == 'm')
        {
          memcpy(message, &line[1], line.length()-1);

          server.write('q');
          keepReading = false;
        }
      }
    }
        
    client.stop();
  }
  
  u8g2.firstPage();
  do
  {
    u8g2.setFont(u8g2_font_t0_11_tf);
    u8g2.drawStr(0, 8, ipStr);
    u8g2.drawStr(0, 17, message);
  } while(u8g2.nextPage());
  delay(10);
}
