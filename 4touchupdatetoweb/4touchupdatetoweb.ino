#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define touchinput D1

const char* ssid = "iQOO";
const char* password = "12345678";

String page = "";
String data = "UNKNOWN"; // Initialize as unknown


ESP8266WebServer server(80);   // Instantiate server at port 80 (http port)


void setup() {
  Serial.begin(115200);
  pinMode(touchinput,INPUT); //set inputpin to 

  WiFi.begin(ssid, password); // Begin WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    // Display HTML page
    page = "<h1 style='text-align: center;'>Welcome to M-PULSE Xtronica 2k24</h1>";
    page += "<h1 style='text-align: center;'>Touch Sensor Status</h1>";

    page += "<form action='/' method='get'>";
    page += "</div>"; // End of button alignment container
    page += "<div id='data-container' 'text-align: center'><h1>Data: " + String(data) + "</h1></div>"; // Data container
    page += "</form>";

    page += "<script>setTimeout(function() { location.reload(); }, 00);</script>"; // Reload page 

    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}


void loop() 
  {
    server.handleClient();
    int response = digitalRead(touchinput); //readinput
    if (response == 1)
      {
        Serial.println("Touched");
        data = "Touched";
      }
    else
      {
        Serial.println("Untouched");
        data = "UnTouched";
      }
  }


