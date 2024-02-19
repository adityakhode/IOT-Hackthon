#include <ESP8266WiFi.h>

// Define RGB LED pins
const int redPin = D2;    // Pin for red color
const int greenPin = D3;  // Pin for green color
const int bluePin = D4;   // Pin for blue color

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Loop through all possible colors
  for (int color = 0; color <= 0xFFFFFF; color++) {
    // Extract individual color components (RGB)
    int red = (color >> 16) & 0xFF;
    int green = (color >> 8) & 0xFF;
    int blue = color & 0xFF;
    Serial.println(color);
    // Set PWM duty cycle for each color channel
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);

    // Delay for 0.5 seconds
  }
}