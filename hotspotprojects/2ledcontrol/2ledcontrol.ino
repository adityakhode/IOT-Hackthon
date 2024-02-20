#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define red D1
#define green D2
#define blue D3

// Replace with your network credentials
const char* ssid = "Hotspot";  // Name of the hotspot
const char* password = ""; // Password for the hotspot

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";

void setup(void) {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  delay(1000);
  Serial.begin(115200);

  // Configure ESP8266 as an Access Point (AP)
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  server.on("/", []() {
    page = "<h1 style='text-align: center;' font-size: 200px;>Set Color</h1>";
    page += "<div style='text-align: center;'>";

    page += "<form action='/' method='post' style='display: inline-block;'>";

    page += "<button type='submit' name='on' value='255' style='font-size: 70px; padding: 15px 30px; background-color: #4CAF50; color: black; border: none; border-radius: 10px;'>on</button></br></br>";
    page += "<button type='submit' name='Red' value='10' style='font-size: 70px; padding: 15px 30px; background-color: #FF5733; color: white; border: none; border-radius: 10px;'>Red</button></br></br>";
    page += "<button type='submit' name='Green' value='20' style='font-size: 70px; padding: 15px 30px; background-color: #33FF57; color: white; border: none; border-radius: 10px;'>Green</button></br></br>";
    page += "<button type='submit' name='Blue' value='30' style='font-size: 70px; padding: 15px 30px; background-color: #3399FF; color: white; border: none; border-radius: 10px;'>Blue</button></br></br>";
    page += "<button type='submit' name='off' value='0' style='font-size: 70px; padding: 15px 30px; background-color: #808080; color: white; border: none; border-radius: 10px;'>off</button></br></br>";
    page += "</form>";

    page += "</div>";
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();

  // Check if a button was pressed
  if (server.hasArg("on")) {
    Serial.println("on");
    analogWrite(red, 255);
    analogWrite(green, 255);
    analogWrite(blue, 255);
  }
  if (server.hasArg("Red")) {
    Serial.println("Red");
    analogWrite(red, 255);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  }
  if (server.hasArg("Green")) {
    Serial.println("Green");
    analogWrite(red, 0);
    analogWrite(green, 255);
    analogWrite(blue, 0);
  }
  if (server.hasArg("Blue")) {
    Serial.println("Blue");
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 255);
  }
  if (server.hasArg("off")) {
    Serial.println("off");
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  }
}
