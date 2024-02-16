// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "esphotspot";
const char* password = "Pass@123";

// Set LED PIN (D4 for NodeMCU)
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Connect to WiFi
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("Access Point IP:");
  Serial.println(myIP);

  // Define HTML content as a string
  String htmls = "<!DOCTYPE html>\
<html>\
<head>\
    <title>ESP8266 LED Control</title>\
    <style>\
        .round-btn {\
            color: white;\
            border: none;\
            border-radius: 50%;\
            width: 200px;\
            height: 200px;\
            font-size: 20px;\
        }\
    </style>\
</head>\
<body>\
    <h1>ESP8266 LED Control</h1>\
    <button class=\"round-btn\" id=\"toggleButton\" onclick=\"toggleLED()\"></button>\
    <script>\
        function toggleLED() {\
            var button = document.getElementById('toggleButton');\
            if (button.innerHTML === 'On') {\
                button.innerHTML = 'Off';\
                button.style.backgroundColor = 'red';\
            } else {\
                button.innerHTML = 'Off';\
                button.innerHTML = 'On';\
                button.style.backgroundColor = 'green';\
            }\
            fetch('/toggle').then(response => { if (response.ok) location.reload(); });\
        }\
    </script>\
</body>\
</html>";

  // Route for root / web page
  server.on("/", HTTP_GET, [htmls](AsyncWebServerRequest *request) {
    request->send(200, "text/html", htmls);
  });

  // Route to toggle LED
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    Serial.println(ledPin);
    request->send(200, "text/plain", "LED toggled");
  });

  // Start server
  server.begin();
}

void loop() {
  // Empty, as we are using AsyncWebServer
}
