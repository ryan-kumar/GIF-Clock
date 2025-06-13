#include "clock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayInit();
  setTimeManually();
}

void loop() {
  displayTime();
}
