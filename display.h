#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include "clock.h"

void displayInit();
void displayTime();
void typeMessage(String message);
void bootMessage();
bool createTouchbx(int stx, int sty, int width, int height);





#endif
