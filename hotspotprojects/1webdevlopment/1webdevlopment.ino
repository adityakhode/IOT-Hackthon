#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Hotspot";
const char* password = "";

String page = "";
String data = "UNKNOWN"; // Initialize as unknown


ESP8266WebServer server(80);   // Instantiate server at port 80 (http port)


void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress apIP = WiFi.softAPIP(); // Get IP address of the AP
  Serial.print("AP IP address: ");
  Serial.println(apIP);

  server.on("/", []() {
    // Display HTML page
    page = "<h1 style='text-align: center;'>Welcome to M-PULSE Xtronica 2k24</h1>";


    //2 comment
    page += "<div style='text-align: center;'>"; // Align buttons to the center
    page += "<form action='/' method='post'>";
    page += "<button type='submit' name='status' value='DAY' style='font-size: 50px; padding: 50px;'>Set Day</button><br><br>";
    page += "<button type='submit' name='status' value='NIGHT' style='font-size: 50px; padding: 20px;'>Set Night</button>";
    page += "</form>";
    

    //3rd comment
    page += "</div>"; // End of button alignment container
    page += "<div id='data-container' 'text-align: center'><h1>Data: " + String(data) + "</h1></div>"; // Data container
    
    page += "<script>setTimeout(function() { location.reload(); }, 1500);</script>"; // Reload page 

    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}


void loop() 
  {
    server.handleClient();
    if (server.hasArg("status")) 
      {
        String newStatus = server.arg("status");
        if (newStatus == "DAY") 
          {
            Serial.println(newStatus);
            data = "Day";
          } 
        else if (newStatus == "NIGHT") 
          {
            data = "Night";
            Serial.println(newStatus);
          }
      }
  }



