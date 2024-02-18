#define touchinput D1
//Define input pin
void setup() 
  {
    Serial.begin(9600);      //input Serial  
    pinMode(touchinput,INPUT); //set inputpin to 
  }

void loop() 
  {
    int response = digitalRead(touchinput); //readinput
    if (response == 1)
      {
        Serial.println("Touched");
      }
    else
      {
        Serial.println("Untouched");
      }
  }
