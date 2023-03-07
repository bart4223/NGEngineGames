#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGDecimalPointCounter.h>

#define DELAY 10

NGColorOLED *cdm = new NGColorOLED();
NGDecimalPointCounter *dpc = new NGDecimalPointCounter(cdm, COLOR_RED);

void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  cdm->initialize();
  cdm->setScale(2);
  cdm->clear();
  dpc->setMaxDigits(5);
  dpc->setPosX(5);
  dpc->setPosY(5);
  dpc->initialize();
  dpc->setCounter(random(1, 1000));
  observeMemory(0);
}

void loop() {
  dpc->processingLoop();
  //dpc->incrementCounter(random(1, 100));
  //delay(DELAY);
}
