#include <M5Cardputer.h>
#include <Adafruit_BMP280.h>
#include "SHTSensor.h"

Adafruit_BMP280 bmp;
SHTSensor sht;
LGFX_Sprite buffer(&M5Cardputer.Display);

// Pole barev pro rotaci
const uint16_t frameColors[] = { DARKGREY, LIGHTGREY };
const int numColors = sizeof(frameColors) / sizeof(frameColors[0]);
int colorIndex = 0;

void setup() {
  M5Cardputer.begin();
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFont(&FreeMono12pt7b);
  M5Cardputer.Display.println("Init");

  if (!bmp.begin(0x76)) {
    M5Cardputer.Display.println("BMP Err");
    while (true) delay(10);
  }
  if (!sht.init()) {
    M5Cardputer.Display.println("SHT Err");
    while (true) delay(10);
  }
  M5Cardputer.Display.println("OK");

  delay(500);

  buffer.createSprite(M5Cardputer.Display.width(), M5Cardputer.Display.height());
  buffer.setTextSize(1);
  buffer.setFont(&Font4);
}

void loop() {
  auto& disp = M5Cardputer.Display;

  float teplota = bmp.readTemperature();
  float tlak = bmp.readPressure() / 100.0F;
  sht.readSample();
  float teplota2 = sht.getTemperature();
  float vlhkost2 = sht.getHumidity();

  int w = disp.width();
  int h = disp.height();

  // Vyber barvu rámečku
  uint16_t frameColor = frameColors[colorIndex];
  colorIndex = (colorIndex + 1) % numColors;

  buffer.fillScreen(BLACK);

  buffer.drawRoundRect(2, 2, w - 4, h - 4, 8, frameColor);

  buffer.setCursor(0, 17);
  buffer.setTextColor(BLUE);
  buffer.printf("    %.1f C\n", teplota);
  buffer.printf("    %.1f hPa\n", tlak);

  buffer.setTextColor(VIOLET);
  buffer.printf("    %.1f C\n", teplota2);
  buffer.printf("    %.1f %%\n", vlhkost2);

  buffer.pushSprite(0, 0);

  Serial.printf("%.1f|%.1f|%.1f|%.1f\n", teplota, tlak, teplota2, vlhkost2);

  delay(2000);
}