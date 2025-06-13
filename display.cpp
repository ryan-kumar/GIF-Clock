#include "display.h"

#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void displayInit() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_PINK);
  tft.setTextWrap(false);
}


void displayTime() {
  String time = getTime();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.print(time);
  delay(1000);
}