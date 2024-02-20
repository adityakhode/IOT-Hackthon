#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Hotspot";
const char* password = "";

String data = "";
int sensor_value = 0;
String page = "";

ESP8266WebServer server(80); 

void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  server.on("/", []() {
    page = "</div>"; // End of button alignment container
    page += "<div id='data-container' 'text-align: center'><h1>Data: " + String(data) + "</h1></div>"; // Data container
    
    page += "<script>setTimeout(function() { location.reload(); }, 1500);</script>"; // Reload page 

    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  sensor_value = analogRead(A0);
  Serial.println(sensor_value);
  if (sensor_value > 900)
    data = "night";
  if (sensor_value <900)
    data = "day";

  server.handleClient();


}
