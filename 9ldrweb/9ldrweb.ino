#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ldr D1

const char* ssid = "PESMODERN";
const char* password = "Student@123";

String page = "";
String data = "UNKNOWN"; // Initialize as unknown

ESP8266WebServer server(80); 

int status ;

void setup() 
  {
    pinMode(ldr,INPUT);
    Serial.begin(115200);

    WiFi.begin(ssid, password); // Begin WiFi connection
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

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
