
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2

const char* ssid     = ""; //Your wifi's SSID goes here
const char* password = ""; //Your wifi's Password goes here

ESP8266WebServer server(80);

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266

String webString = "";
unsigned long previousMillis = 0;
const long interval = 2000;
 
void setup(void)
{
  Serial.begin(115200);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.print("\n\r \n\rConnecting to WiFi network");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("DHT Weather Reading Server");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    int celcius = (int)dht.readTemperature();
    int fahrenheit = (int)dht.readTemperature(true);
    int humidity = (int)dht.readHumidity();
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Max-Age", "10000");
    server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    webString = "{\"celcius\": \"" + String(celcius) + "\", \"fahrenheit\":\"" + String(fahrenheit) + "\", \"humidity\" : \"" + String(humidity) + "\"}";
    server.send(200, "application/json", webString);
  });
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void)
{
  server.handleClient();
}
