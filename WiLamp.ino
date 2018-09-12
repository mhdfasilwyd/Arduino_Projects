// WiLamp Version 1
// Made by Muhammed Fasil K-https://github.com/mhdfasilwyd/Arduino_Projects
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>WiLamp</h1><br>
  Ciclk to turn <a href="ledOn">LED ON</a><br>
  Ciclk to turn <a href="ledOff">LED OFF</a><br>
  </center> 
  </body>
  </html>
)=====";
IPAddress staticIP(192, 168, 43, 90); 
IPAddress gateway(192, 168, 43, 1);   
IPAddress subnet(255, 255, 255, 0);  
IPAddress dns(8, 8, 8, 8);  //DNS
const char* deviceName = "pcweek";
#define LED 2  
const char* ssid = "pcweek";
const char* password = "wilamp123";
ESP8266WebServer server(80); 
void handleRoot() 
{
 String s = MAIN_page; 
 server.send(200, "text/html", s); 
}
void handleLEDon() { 
 Serial.println("LED on page");
 digitalWrite(LED,LOW); 
 server.send(200, "text/html", "LED is ON"); 
}
void handleLEDoff() 
{ 
 Serial.println("LED off page");
 digitalWrite(LED,HIGH); //LED off
 server.send(200, "text/html", "LED is OFF"); 
}
void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password); 
  Serial.println(""); 
  pinMode(LED,OUTPUT); 
  digitalWrite(LED,HIGH);
  WiFi.disconnect(); 
  WiFi.hostname(deviceName); 
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  server.on("/", handleRoot);      
  server.on("/ledOn", handleLEDon); 
  server.on("/ledOff", handleLEDoff);
  server.begin();                 
  Serial.println("WiLamp Server Started");
}
void loop(void){
server.handleClient();         
}
