#include <M5Cardputer.h>
#include <Adafruit_BMP280.h>
#include "SHTSensor.h"

// BMP280 senzoru obvykle používá I2C adresu 0x76 nebo 0x77
Adafruit_BMP280 bmp;
SHTSensor sht;

void setup() {
  // Inicializace Cardputeru
  M5Cardputer.begin();
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFont(&FreeMonoBold12pt7b);
  M5Cardputer.Display.setCursor(0, 0);
  M5Cardputer.Display.println("Init");
  //M5Cardputer.Ex_I2C.begin();

  // Inicializace I2C na portu A (GPIO1 = SDA, GPIO2 = SCL)
  //Wire.begin(1, 2);

  if (!bmp.begin(0x76)) {
    M5Cardputer.Display.println("BMP Err");
    while (true) delay(10);
  }

  if(!sht.init()) {
    M5Cardputer.Display.println("SHT Err");
    while (true) delay(10);
  }

  M5Cardputer.Display.println("OK");
  delay(1000);
  M5Cardputer.Display.clear();
  Serial.begin(115200);
}

void loop() {
  auto disp = M5Cardputer.Display;

  float teplota = bmp.readTemperature();
  float tlak = bmp.readPressure() / 100.0F; // Převod na hPa

  sht.readSample();
  float teplota2 = sht.getTemperature();
  float vlhkost2 = sht.getHumidity();

  disp.setCursor(0, 0);
  disp.clear();
  disp.setTextColor(BLUE);
  disp.printf("\n %.1f C\n", teplota);
  disp.printf(" %.1f hPa\n", tlak);
  disp.setTextColor(VIOLET);
  disp.printf(" %.1f C\n", teplota2);
  disp.printf(" %.1f %%\n", vlhkost2);

  Serial.printf("%.1f|%.1f|%.1f|%.1f\n", teplota, tlak, teplota2, vlhkost2);

  delay(2000);
}