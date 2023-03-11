#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGDecimalPointCounter.h>

#define SCALE       3
#define DELAY   10000
#define RANGE 1000000

NGColorOLED *cdm = new NGColorOLED();
NGDecimalPointCounter *dpc = new NGDecimalPointCounter(cdm, COLOR_RED);

long _lastValue = 0;

void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
  dpc->setMaxDigits(5);
  dpc->setShowMaxDigits(false);
  dpc->setIsAnimationEnabled(true);
  dpc->setAnimationDelay(100);
  dpc->setPosX(5);
  dpc->setPosY(5);
  dpc->initialize();
  dpc->setCounter(random(1, RANGE));
  observeMemory(0);
}

void loop() {
  dpc->processingLoop();
  if (millis() - _lastValue > DELAY) {
    cdm->clear();
    dpc->setCounter(random(1, RANGE));
    _lastValue = millis();
  }
  //dpc->incrementCounter(random(1, RANGE));
  //dpc->setCounter(random(1, RANGE));
  //delay(DELAY);
}
