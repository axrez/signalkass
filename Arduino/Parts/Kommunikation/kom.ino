#include <SPI.h>
#define led 22

static const int spiClk = 800000; // 1kHz

SPIClass * vspi = NULL;

void setup() {
  vspi = new SPIClass(VSPI);

  vspi->begin();

  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(5, OUTPUT);

  
}



void loop() {
  Serial.println(collectData());
  delay(10000);
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
  }
}
