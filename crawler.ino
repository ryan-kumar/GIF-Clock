#include "clock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayInit();
  bootMessage();


}

void loop() {
  displayTime();
  delay(100);
}