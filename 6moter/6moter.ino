#define moter D1

void setup() 
  {
    pinMode(moter,OUTPUT);
  }

void loop() 
{
  //digitalWrite(moter,HIGH);
  //delay(2000);
  //analogWrite(moter,255);
  //delay(2000);
  //analogWrite(moter,100);
  //delay(5000);
  analogWrite(moter,90);
  delay(5000);
}
