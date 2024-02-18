#include <ESP8266WiFi.h>

const int touchPin = D1;
volatile int tapCount = 0;  
unsigned long lastTapTime = 0;  




void setup() {
  pinMode(touchPin, INPUT);  
  Serial.begin(115200);
}

void loop() 
{
  if (digitalRead(touchPin))
    {
      unsigned long now = millis();
      if (now - lastTapTime > 100 && now - lastTapTime <1200) 
        {
          tapCount++; 
        } 
      else if (now - lastTapTime >1500)
        {
          Serial.println(tapCount);
          tapCount = 1; 
        }
      lastTapTime = now;
    }
    delay(100);
}
