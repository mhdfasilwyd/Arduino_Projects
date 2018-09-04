#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//ESP Web Server Library to host a web page
#include <ESP8266WebServer.h>
//Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>WiFi Lamp</h1><br>
  Ciclk to turn <a href="ledOn">LED ON</a><br>
  Ciclk to turn <a href="ledOff">LED OFF</a><br>
  </center> 
  </body>
  </html>
)=====";
//Static IP address configuration
IPAddress staticIP(192, 168, 43, 90); //ESP static ip
IPAddress gateway(192, 168, 43, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
const char* deviceName = "pcweek";
#define LED 2  
const char* ssid = "pcweek";
const char* password = "wilamp123";
ESP8266WebServer server(80); 
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); //LED is connected in reverse
 server.send(200, "text/html", "LED is ON"); //Send ADC value only to client ajax request
}

void handleLEDoff() { 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 server.send(200, "text/html", "LED is OFF"); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password); //Connect to your WiFi router
  Serial.println(""); 
  pinMode(LED,OUTPUT); //Onboard LED port Direction output
  //Power on LED state off
  digitalWrite(LED,HIGH);
  WiFi.disconnect();  //Prevent connecting to wifi based on previous configuration
  WiFi.hostname(deviceName); // DHCP Hostname (useful for finding device for static lease)
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/ledOn", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ledOff", handleLEDoff);
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();          //Handle client requests
}
