#include "clock.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  displayInit();
  setTimeManually(2, 36);
  typeMessage("Hello? Can you hear me?");
  typeMessage("This is a test of the typewriting feature...");
  typeMessage("I Hope you are liking it!");

}

void loop() {
  displayTime();
}
