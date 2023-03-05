#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGDecimalPointCounter.h>

#define DELAY 10

NGColorOLED *cdm = new NGColorOLED();
NGDecimalPointCounter *dpc = new NGDecimalPointCounter(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setScale(2);
  cdm->clear();
  dpc->setDigits(5);
  dpc->setPosX(5);
  dpc->setPosY(5);
  dpc->initialize();
  dpc->setCounter(0);
  observeMemory(0);
}

void loop() {
  dpc->processingLoop();
  dpc->incrementCounter(random(1, 100));
  delay(DELAY);
}
