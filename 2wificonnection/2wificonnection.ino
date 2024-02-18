#include <ESP8266WiFi.h>


const char* ssid = "iQOO";
const char* password = "12345678";


void setup() 
  {
    Serial.begin(9600);
    WiFi.begin(ssid, password); //begin WiFi connection
     while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  }

void loop() {
  // put your main code here, to run repeatedly:

}
