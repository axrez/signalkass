#include <WiFi.h> //Wifi library
#include "esp_wpa2.h" //wpa2 library for connections to Enterprise networks
#include <HTTPClient.h>
#include <Wire.h>
#include <SSD1306.h> 
#include <SPI.h>

#define EAP_ANONYMOUS_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_IDENTITY "ZBC-AND-14@efif.dk"
#define EAP_PASSWORD "Fri3Kulmule7"

const char* ssid = "ZBC WiFi"; // Eduroam SSID

SSD1306Wire display(0x3c, 21, 22, GEOMETRY_128_32);

WiFiClient client;

static const int spiClk = 800000; // 1kHz
SPIClass * vspi = NULL;

void setup() {
  vspi = new SPIClass(VSPI);
  Serial.begin(115200);

  pinMode(5, OUTPUT);
  pinMode(36, INPUT);

  vspi->begin();
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

  display.drawString(0,0, "Connected");
  display.display();

  delay(500);
}

void loop() {
  updateStateDisplay(false);
  postReq(collectData());
  updateStateDisplay(true);
  delay(20000);
}

String collectData() { 
  String data = String();
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  //pull SS slow to prep other end for transfer
  digitalWrite(5, LOW); 
  int m = vspi->transfer16(1);
  Serial.println(m);
  for(int i = 0; i < 1000; i++) {
    int n = vspi->transfer16(0);
    data += n;
    data += ", ";
    delay(1);
  }
  //pull ss high to signify end of data transfer
  digitalWrite(5, HIGH); 
  vspi->endTransaction();
  return(data);
}

void postReq(String body) {
  if(WiFi.status() == WL_CONNECTED)  {
    HTTPClient http;

    http.begin("https://signalkass.herokuapp.com/api/device/post");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    body = "data=" + body;
    int httpCode = http.POST(body);

    Serial.println(httpCode);
    if(httpCode > 0) {
      String payload = http.getString();
        Serial.println(httpCode);
      Serial.println(payload);
    } else {
      Serial.println("Error in req");
    }
    http.end();
  }
}

void updateBatteryDisplay() {
  String msg = "U: ";
  msg += (analogRead(36)/535.0 );
  msg += " V";
  display.drawString(0,16, msg);
}

void updateStateDisplay(bool completed) {
  if (completed) {
    display.clear();
    display.drawString(0,0, "Success!");
    updateBatteryDisplay();
    display.display();
  } else {
    display.clear();
    display.drawString(0,0, "Posting...");
    updateBatteryDisplay();
    display.display();
  }
}
