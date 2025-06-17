#include "display.h"

#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4
#define TCS_PIN 5
#define TIRQ_PIN 21

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TCS_PIN, TIRQ_PIN);

void displayInit() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  ts.setRotation(1);
}

bool createTouchbx(int stx, int sty, int width, int height) {
  tft.drawRect(stx, sty, width, height, ILI9341_BLUE); //optional: draw hitbox
  bool touched = false;
  if (ts.touched()) {
  TS_Point p = ts.getPoint();

  int x = map(p.x, 3900, 400, 0, 320);
  int y = map(p.y, 3700, 300, 0, 240);

  touched = (x >= stx && x <= stx + width && y >= sty && y <= sty + height);
  Serial.println("Touch captured at: " + String(x) + ", " + String(y) + " hit: " + String(touched));

  }
  return touched;
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

void wipeTime(int hours, int minutes, int seconds, int half) {
  tft.fillRect(30, 100, 280, 40, ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.print(pad(hours)); tft.print(":");
  tft.print(pad(minutes)); tft.print(":");
  tft.print(pad(seconds)); tft.print(half == 0 ? " AM" : " PM");

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
  int hours = 12; int minutes = 0; int seconds = 0; int half = 0;
  while (!submitted) {
    if (createTouchbx(40, 60, 20, 25)){
      hours = (hours +1) % 12 == 0 ?  12 : (hours +1) % 12;
      wipeTime(hours, minutes, seconds, half);
    } 
    else if (createTouchbx(112, 60, 20, 25)){
       minutes = (minutes + 1) % 60;
       wipeTime(hours, minutes, seconds, half);
    } 
    else if (createTouchbx(184, 60, 20, 25)){
       seconds = (seconds + 1) % 60;
       wipeTime(hours, minutes, seconds, half);
    } 
    else if (createTouchbx(256, 60, 20, 25)){
       half = (half + 1) % 2;
       wipeTime(hours, minutes, seconds, half);
    } 
    // attach the other settings
    submitted = createTouchbx(170, 180, 90, 30);    
    delay(250);
  }
  setTimeManually(hours, minutes);
}
