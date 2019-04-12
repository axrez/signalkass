#include <WiFi.h> //Wifi library
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#include <HTTPClient.h>
#include <Wire.h>
#include <SSD1306.h> 

#define EAP_ANONYMOUS_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_PASSWORD "Fri3Kulmule7"

const char* ssid = "ZBC WiFi"; // Eduroam SSID

SSD1306Wire display(0x3c, 21, 22, GEOMETRY_128_32);

WiFiClient client;

void setup() {
  Serial.begin(115200);
  display.init();
  display.setFont(ArialMT_Plain_16);
  String initStr = "Connecting to network";
  Serial.println(ssid);
  display.drawString(0, 0, initStr);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);

  WiFi.begin(ssid);

  int i = 0;
  while(WiFi.status() != WL_CONNECTED) {
    display.drawString(0 + i , 16 , ".");
    display.display();
    i += 3;
    delay(500);
    Serial.print(".");
  }
  display.clear();
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  display.drawString(0,0, "Hej");
  display.display();

  delay(500);
}

void loop() {
  postReq();
}

void postReq() {
  if(WiFi.status() == WL_CONNECTED)  {
    HTTPClient http;

    http.begin("https://movia-demo.herokuapp.com/api/update");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int httpCode = http.POST("key=b6aacadbc34a9144d78f5e655eb97c08b14c1c6f58f1bf9e3733490631283f67&busid=2&c=25");

    Serial.println(httpCode);
    if(httpCode > 0) {
      String payload = http.getString();
        Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error in req");
    }
    http.end();

    delay(10000);
  }
}

