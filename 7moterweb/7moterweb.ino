#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "PESMODERN";
const char* password = "Student@123";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
String data = "UNKNOWN"; // Initialize as unknown

void setup(void) {
  pinMode(5, OUTPUT);
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
  Serial.println("");
  
  // Wait for connection
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
    page = "<h1>Sensor to Node MCU Web Server</h1>";
    page += "<h3>Data:</h3> <h4>" + String(data) + "</h4>";
    page += "<form action='/' method='post'>";
    page += "<button type='submit' name='START' value='4'>Set START</button>";
    page += "<button type='submit' name='speed1' value='1'>Set SPEED 1</button>";
    page += "<button type='submit' name='speed2' value='2'>Set SPEED 2</button>";
    page += "<button type='submit' name='speed3' value='3'>Set SPEED 3</button>";
    page += "<button type='submit' name='speed4' value='4'>Set SPEED 4</button>";
    page += "<button type='submit' name='STOP' value='4'>Set STOP </button>";
    page += "</form>";
    //page += "<script>setTimeout(function() { location.reload(); }, 5000);</script>"; // Reload page every 10 seconds
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();

  int x = digitalRead(5);
  
  // Check sensor state
  if (x == 0) {
    data = "DAY";
  } else {
    data = "NIGHT";
  }

  // Check if a button was pressed
  if (server.hasArg("START"))
    {
      Serial.println("START");
      analogWrite(5,125);

    }
  if (server.hasArg("STOP"))
    {
      Serial.println("STOP");
      analogWrite(5,0);

    }
  if (server.hasArg("speed1"))
    {
      Serial.println("Speed1");
      analogWrite(5,70);

    }
    if (server.hasArg("speed2"))
    {
      Serial.println("Speed2");
      analogWrite(5,120);
    }
    if (server.hasArg("speed3"))
    {
      Serial.println("Speed3");
      analogWrite(5,180);
    }
    if (server.hasArg("speed4"))
    {
      Serial.println("Speed4");
      analogWrite(5,255);
    }

}