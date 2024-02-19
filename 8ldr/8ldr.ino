#define ldr D1

int status ;

void setup() 
  {
    pinMode(ldr,INPUT);
    Serial.begin(115200);
  }

void loop() 
  {
    status = digitalRead(ldr);
    if (status == 0)
      Serial.println("Day");
    else
      Serial.println("Night");
  }
