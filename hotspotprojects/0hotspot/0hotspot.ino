#include <ESP8266WiFi.h>

const char* ssid = "Hotspot";
const char* password = "";

void setup() 
{
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  Serial.print("AP IP address: ");
  Serial.println(apIP);
}

void loop() {

}
