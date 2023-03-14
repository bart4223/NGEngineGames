#include <NGMemoryObserver.h>
#include <NGColorOLED.h>

#define DELAY 3000

NGColorOLED co = NGColorOLED();

void setup() {
  char log[100];
  observeMemory(0);
  co.initialize();
  co.clear();
  co.setScale(5);
  co.beginUpdate();
  co.drawPoint(0, 0, COLOR_RED);
  co.endUpdate();
  sprintf(log, "Width: %d Height: %d", co.getWidth(), co.getHeight());
  Serial.println(log);
  observeMemory(0);
}

void loop() {
  observeMemory(DELAY);
}
