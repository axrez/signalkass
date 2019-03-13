#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <SSD1306.h> 
 
const char* ssid = "signalkass";
const char* password = "12345678";

WebServer server(80);

const int led = 13;

SSD1306Wire display(0x3c, 21, 22, GEOMETRY_128_32);
 
bool displayAddress = false;

int dTime = 0;
int tempTime = 0;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp32!");
  digitalWrite(led, 0);
}

void displayCredentials() {
  display.clear();
  String ssids = "SSID: " + String(ssid);
  String passwords = "PASS: " + String(password);
  display.drawString(0,0, ssids);
  display.drawString(0, 16, passwords);
  display.display();
}

void displayIp() {
  display.clear();
  String IP = "IP: " + WiFi.softAPIP().toString();
  display.drawString(0,0, IP);
  display.display();
}

void switchDisplay() {
  tempTime = millis();
  if(dTime + 2500 < tempTime) {
    if(displayAddress) {
      displayIp();
      dTime = millis();
      displayAddress = false;
    } else {
      displayCredentials();
      dTime = millis();
      displayAddress = true;
    }
  }
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  display.init();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0,0, "Starting");
  display.display();
  WiFi.softAP(ssid, password);
  server.on("/", handleRoot);
  server.begin();
  dTime = millis();
}

void loop() {
  server.handleClient();
  switchDisplay();
}
