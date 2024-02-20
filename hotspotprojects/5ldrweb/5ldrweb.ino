#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ldr D1

const char* ssid = "Hotspot";
const char* password = "";

String page = "";
String data = "UNKNOWN"; // Initialize as unknown

ESP8266WebServer server(80); 

int status ;

void setup() 
  {
    pinMode(ldr,INPUT);
    Serial.begin(115200);

    WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  Serial.print("AP IP address: ");
  Serial.println(apIP);

    server.on("/", []() 
    {
    // Display HTML page
    page = "<h1 style='text-align: center;'>LDR Senses </h1>";
    page += "</div>"; // End of button alignment container
    page += "<div id='data-container' 'text-align: center'><h1>Data: " + String(data) + "</h1></div>";
    page += "<script>setTimeout(function() { location.reload(); }, 1500);</script>";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
  }

void loop() 
  {
    server.handleClient();
    status = digitalRead(ldr);
    if (status == 0)
      {
        Serial.println("Day");
        data = "Day";
      }
    else
      {
        Serial.println("Night");
        data = "Night";
      }
  }
