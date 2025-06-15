#include "clock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayInit();
  setTimeManually(2, 36);
  bootMessage();


}

void loop() {
  displayTime();
}
