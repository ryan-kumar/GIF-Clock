#include "clock.h"
#include "display.h"


bool tick = false;
void setup() {
  Serial.begin(115200);
  displayInit();
  bootSequence();
  //typeMessage("This is a test of the new dialog box");


}

void loop() {
  tick = tick ? false : true;
  displayTime(tick);
  delay(100);
}
