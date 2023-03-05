#include <NGMemoryObserver.h>
#include <NGColorOLED.h>

#define DELAY 3000

NGColorOLED co = NGColorOLED();

void setup() {
  observeMemory(0);
  co.initialize();
  co.clear();
  co.setScale(1);
  co.beginUpdate();
  co.drawPoint(0, 0, COLOR_RED);
  co.endUpdate();
  observeMemory(0);
}

void loop() {
  observeMemory(DELAY);
}
