#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

# define red D1
# define green D2
# define blue D3
// Replace with your network credentials

//const char* ssid = "Satvik-2G";
//const char* password = "Ishan@7038";

const char* ssid = "i";
const char* password = "";

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";


void setup(void) {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  
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
    page = "<h1>Set Color</h1>";
    page += "<form action='/' method='post'>";

    page += "<button type='submit' name='on' value=255>on</button>";
    page += "<button type='submit' name='Red' value=10>Red</button>";
    page += "<button type='submit' name='Green' value=20>Green</button>";
    page += "<button type='submit' name='Blue' value=30>Blue</button>";
    page += "<button type='submit' name='off' value=0>off</button>";

    page += "</form>";
    //page += "<script>setTimeout(function() { location.reload(); }, 5000);</script>"; // Reload page every 10 seconds
    server.send(200, "text/html", page);
  });
  
  server.begin();
  Serial.println("Web server started!");
}

void loop(void) {
  server.handleClient();

  // Check if a button was pressed
  if (server.hasArg("on"))
    {
      String startValue = server.arg("START");
      Serial.println(startValue);
      analogWrite(red,255);
      analogWrite(green,255);
      analogWrite(blue,255);
    }
  if (server.hasArg("Red"))
    {
      String startValue = server.arg("Red");
      Serial.println(startValue);
      analogWrite(red , 255);
      analogWrite(green , 0);
      analogWrite(blue , 0);
    }
  if (server.hasArg("Green"))
    {
      String startValue = server.arg("Green");
      Serial.println(startValue);
      analogWrite(red , 0);
      analogWrite(green,255);
      analogWrite(blue , 0);

    }
    if (server.hasArg("Blue"))
    {
      String startValue = server.arg("Blue");
      Serial.println(startValue);
      analogWrite(red , 0);
      analogWrite(green , 0);
      analogWrite(blue , 255);
    }
    if (server.hasArg("off"))
    {
      String startValue = server.arg("off");
      Serial.println(startValue);
      analogWrite(red,0);
      analogWrite(green,0);
      analogWrite(blue,0);
    }
}