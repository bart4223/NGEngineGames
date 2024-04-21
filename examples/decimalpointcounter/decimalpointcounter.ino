#define OLED //OLED, DOTMATRIX

#include <NGMemoryObserver.h>
#include <NGZX81Font.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#include <NGDecimalPointCounter.h>

#ifdef OLED
#define SCALE       3
#define RANGE 1000000
#define DELAY   10000
#endif
#ifdef DOTMATRIX
#define SCALE       1
#define RANGE    1000
#define DELAY   10000
#endif

NGZX81Font *fontZX81 = new NGZX81Font();

#ifdef OLED
NGColorOLED *cdm = new NGColorOLED();
#endif
#ifdef DOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#endif
NGDecimalPointCounter *dpc = new NGDecimalPointCounter(cdm, COLOR_RED);

long _lastValue = 0;

void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
  #ifdef OLED
  dpc->setMaxDigits(5);
  #endif
  #ifdef DOTMATRIX
  dpc->setMaxDigits(3);
  #endif
  dpc->setShowMaxDigits(false);
  dpc->setIsAnimationEnabled(true);
  dpc->setAnimationDelay(100);
  dpc->setFont(fontZX81);
  #ifdef OLED
  dpc->setPosX(5);
  dpc->setPosY(5);
  #endif
  #ifdef DOTMATRIX
  dpc->setPosX(0);
  dpc->setPosY(0);
  #endif
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
