#include "display.h"

#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4
#define TCS_PIN 5
#define TIRQ_PIN 21

#define LAVENDER 0xA3B9
#define PASTEL_PINK 0xDDDE

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
  //tft.drawRect(stx, sty, width, height, ILI9341_BLUE); //optional: draw hitbox
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


void displayTime(bool tick) {
  String time = getTime();
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextSize(2);
  uint16_t color = ILI9341_WHITE;
  tft.setTextColor(color);
  tft.setCursor(10, 20);
  if (tick){
    tft.println(String((char)3) + " - " + String((char)3) + " - " + String((char)3) + " - "   + String((char)3) + " - "   
      + String((char)3) + " - "   + String((char)3) + " - "   + String((char)3));
  } else {
    tft.println( " - "   + String((char)3) + " - " + String((char)3) + " - " + String((char)3) + " - "   + String((char)3) + " - "   
      + String((char)3) + " - " + String((char)3) + " - " );
  }
 
  
  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.println(time);

  String date = getDate();
  tft.setTextSize(2);
  tft.setCursor(90, 140);
  tft.println(date);


  delay(1000);
}

// void makeMessageBox() {

// }

void typeMessage(String message) {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, 320, 50, PASTEL_PINK);
  tft.fillRect(0, 0, 320, 5, LAVENDER);
  tft.fillRect(0, 50, 320, 2, LAVENDER);
  tft.fillRect(0, 0, 3, 50, LAVENDER);
  tft.fillRect(318, 0, 3, 50, LAVENDER);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10,10);
  for (int i = 0; i < message.length(); ++i) {
    tft.print(message[i]);
    delay(75);
  }
  delay(1000);
}

void wipeTime(int hours, int minutes, int seconds) {
  tft.fillRect(30, 100, 280, 40, ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.print(pad((hours) % 12 == 0 ?  12 : (hours) % 12)); tft.print(":");
  tft.print(pad(minutes)); tft.print(":");
  tft.print(pad(seconds)); tft.print((hours > 11) ? " PM" : " AM");
}

void wipeDate(int month, int day, int year) {
  tft.fillRect(30, 100, 280, 40, ILI9341_BLACK);
  tft.setTextSize(4);
  tft.setCursor(30, 100);
  tft.print(pad(month + 1)); tft.print("/");
  tft.print(pad(day + 1)); tft.print("/");
  tft.print(pad(1900 + year));
}

void bootSequence() {
  typeMessage("Yaaaaaawwwwwnnn......");
  typeMessage("I was asleep for quite a while");
  typeMessage("Can you tell me what time it is now?");
  tft.setTextColor(ILI9341_PINK);
  tft.setTextSize(4);
  tft.setCursor(40, 60);
  tft.println("+  +  +");
  int hours = 0; int minutes = 0; int seconds = 0; 
  wipeTime(hours, minutes, seconds);
  tft.setCursor(40, 140);
  tft.println("-  -  -");
  tft.drawRect(170, 180, 90, 30, ILI9341_PINK);
  tft.setTextSize(1);
  tft.setCursor(185, 190);
  tft.println("That's it!");
  bool submitted = false;
  while (!submitted) {
    if (createTouchbx(40, 60, 20, 25)){
      hours = (hours +1) % 24;
      wipeTime(hours, minutes, seconds);
    } 
    else if (createTouchbx(112, 60, 20, 25)){
       minutes = (minutes + 1) % 60;
      wipeTime(hours, minutes, seconds);
    } 
    else if (createTouchbx(184, 60, 20, 25)){
       seconds = (seconds + 1) % 60;
      wipeTime(hours, minutes, seconds);
    } 
    // minus handler
    else if (createTouchbx(40, 140, 20, 25)){
       hours = (--hours <  0) ? 23 : hours;
       wipeTime(hours, minutes, seconds);
    } 
    else if (createTouchbx(112, 140, 20, 25)){
       minutes = (--minutes <  0) ? 59 : minutes;
       wipeTime(hours, minutes, seconds);
    } 
    else if (createTouchbx(184, 140, 20, 25)){
       seconds = (--seconds <  0) ? 59 : seconds;
        wipeTime(hours, minutes, seconds);
    } 
    // attach the other settings
    submitted = createTouchbx(170, 180, 90, 30);    
    delay(250);
  }
  typeMessage("Thank You! `~`");
  typeMessage("If you don't mind...");
  typeMessage("can you also tell me what day it is?");
  tft.setTextSize(4);
  tft.setCursor(40, 60);
  tft.setTextColor(ILI9341_PINK);
  tft.println("+  +  +");
  int month = 0; int day = 0; int year = 125; 
  wipeDate(month, day, year);
  tft.setCursor(40, 140);
  tft.println("-  -  -");
  tft.drawRect(170, 180, 90, 30, ILI9341_PINK);
  tft.setTextSize(1);
  tft.setCursor(185, 190);
  tft.println("That's it!");
  submitted = false;
   while (!submitted) {
    if (createTouchbx(40, 60, 20, 25)){
      month = (month + 1) % 12;
      wipeDate(month, day, year);
    } 
    else if (createTouchbx(112, 60, 20, 25)){
      day = (day + 1) % 31;
      wipeDate(month, day, year);
    } 
    else if (createTouchbx(184, 60, 20, 25)){
      year++;
      wipeDate(month, day, year);
    } 
    // minus handler
    else if (createTouchbx(40, 140, 20, 25)){
      month = (--month <  0) ? 11 : month;
      wipeDate(month, day, year);
    } 
    else if (createTouchbx(112, 140, 20, 25)){
      day = (--day < 0) ? 30 : day;
      wipeDate(month, day, year);
    } 
    else if (createTouchbx(184, 140, 20, 25)){
      year = (--year < 0) ? 0 : year;
      wipeDate(month, day, year);
    } 
    // attach the other settings
    submitted = createTouchbx(170, 180, 90, 30);    
    delay(250);
  }

  setTimeManually(hours, minutes, seconds, month, day, year);
}
