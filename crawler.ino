#include "clock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayInit();
  setTimeManually(10, 57);
  bootMessage();


}

void loop() {
  displayTime();
}