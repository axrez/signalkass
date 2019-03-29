#include <WiFi.h> //Wifi library
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#include <HTTPClient.h>

#define EAP_ANONYMOUS_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_PASSWORD "Fri3Kulmule7"

const char* ssid = "ZBC WiFi"; // Eduroam SSID
const char* host = "movia-demo.herokuapp.com";
const String url = "/api/update";

WiFiClient client;

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to network: ");
  Serial.println(ssid);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);

  esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_ANONYMOUS_IDENTITY, strlen(EAP_ANONYMOUS_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
  esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
  esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();
  esp_wifi_sta_wpa2_ent_enable(&config);

  WiFi.begin(ssid);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

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
    int httpCode = http.POST("key=&busid=2&c=35");

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

