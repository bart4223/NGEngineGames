#define DOTMATRIX8x32 //OLED, COLORDOTMATRIX, LEDSTRIP, DOTMATRIX8x8, DOTMATRIX8x32
#define FONTDEFAULT //FONTDEFAULT, FONTZX81

#include <NGMemoryObserver.h>
#include <NGZX81Font.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef COLORDOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#define LEDSTRIPBRIGHTNESS 0.05
#endif
#ifdef DOTMATRIX8x8
#include <Visuals/NG8x8DotMatrix.h>
#define DOTMATRIXBRIGHTNESS 0.05
#endif
#ifdef DOTMATRIX8x32
#include <Visuals/NG8x8DotMatrix.h>
#define DOTMATRIXBRIGHTNESS 0.05
#endif
#include <NGDecimalPointCounter.h>

#ifdef OLED
#define SCALE       3
#define RANGE 1000000
#define DELAY   10000
#endif
#ifdef COLORDOTMATRIX
#define SCALE       1
#define RANGE    1000
#define DELAY   10000
#endif
#ifdef LEDSTRIP
#define SCALE       1
#define RANGE    1000
#define DELAY   10000
#endif
#ifdef DOTMATRIX8x8
#define SCALE       1
#define RANGE      10
#define DELAY    1000
#endif
#ifdef DOTMATRIX8x32
#define SCALE       1
#define RANGE      10
#define DELAY     100
#endif

#ifdef FONTZX81
NGZX81Font *fontZX81 = new NGZX81Font();
#endif

#ifdef OLED
NGColorOLED *cdm = new NGColorOLED();
#endif
#ifdef COLORDOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#endif
#ifdef DOTMATRIX8x8
NG8x8DotMatrix *cdm = new NG8x8DotMatrix();
#endif
#ifdef DOTMATRIX8x32
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(4, 8, 32, dmamInverse);
#endif
#ifdef LEDSTRIP
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
NGDecimalPointCounter *dpc = new NGDecimalPointCounter(cdm, COLOR_RED);

#define ANIMATIONDELAY 100

long _lastValue = 0;
bool _init = true;

void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #endif
  #ifdef OLED
  cdm->initialize();
  #endif
  #ifdef COLORDOTMATRIX
  cdm->initialize();
  #endif
  #ifdef DOTMATRIX8x8
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  #endif
  #ifdef DOTMATRIX8x32
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  #endif
  cdm->setScale(SCALE);
  cdm->clear();
  #ifdef OLED
  dpc->setMaxDigits(5);
  #endif
  #ifdef COLORDOTMATRIX
  dpc->setMaxDigits(3);
  #endif
  #ifdef DOTMATRIX8x8
  dpc->setMaxDigits(1);
  #endif
  #ifdef DOTMATRIX8x32
  dpc->setMaxDigits(4);
  #endif
  dpc->setShowMaxDigits(false);
  dpc->setIsAnimationEnabled(true);
  dpc->setAnimationDelay(ANIMATIONDELAY);
  #ifdef FONTZX81
  dpc->setFont(fontZX81);
  #endif
  #ifdef OLED
  dpc->setPosX(5);
  dpc->setPosY(5);
  #endif
  #ifdef COLORDOTMATRIX
  dpc->setPosX(0);
  dpc->setPosY(0);
  #endif
  #ifdef DOTMATRIX8x8
  dpc->setPosX(0);
  dpc->setPosY(0);
  #endif
  #ifdef DOTMATRIX8x32
  dpc->setPosX(0);
  dpc->setPosY(0);
  #endif
  dpc->initialize();
  observeMemory(0);
}

void loop() {
  dpc->processingLoop();
  if (millis() - _lastValue > DELAY | _init) {
    _init = false;
    //cdm->clear();
    //int count = random(1, RANGE);
    //Serial.println(count);
    //dpc->setCounter(0);
    //dpc->setCounter(count);
    dpc->incrementCounter(1);
    _lastValue = millis();
  }
  //dpc->incrementCounter(random(1, RANGE));
  //dpc->setCounter(random(1, RANGE));
  //delay(DELAY);
}