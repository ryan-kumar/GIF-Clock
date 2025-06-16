#include "display.h"

#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void displayInit() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}


void displayTime() {
  String time = getTime();
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.println(time);

  String date = getDate();
  tft.setTextSize(2);
  tft.setCursor(90, 140);
  tft.println(date);


  delay(1000);
}

void typeMessage(String message) {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10,10);
  for (int i = 0; i < message.length(); ++i) {
    tft.print(message[i]);
    delay(75);
  }
  delay(1000);
}

void bootMessage() {
  typeMessage("Yaaaaaawwwwwnnn......");
  typeMessage("I was asleep for quite a while");
  typeMessage("Can you tell me what time it is now?");
  String time = getTime();
  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(4);
  tft.setCursor(40, 60);
  tft.println("+  +  +  +");
  tft.setCursor(30, 100);
  tft.println(time);
   tft.setCursor(40, 140);
  tft.println("-  -  -  -");
  tft.drawRect(170, 180, 90, 30, ILI9341_PINK);
   tft.setTextSize(1);
  tft.setCursor(185, 190);
  tft.println("That's it!");
  bool submitted = false;
  //while (!submitted) {}
  delay(200);
}