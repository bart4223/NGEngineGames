#define LEDSTRIP    //OLED, DOTMATRIX, LEDSTRIP
#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256
//#define RANDOMCOLOR

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#include <NGColorDotMatrixEffectStarLights.h>

#ifdef OLED
#define SCALE       6
#define MINDELAY   60
#define MAXDELAY  120
#endif
#ifdef DOTMATRIX
#define SCALE      1
#define MINDELAY   6
#define MAXDELAY  16
#endif

#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN 8
#define SCALE       1
#ifdef LEDSTRIP100
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#endif
#ifdef LEDSTRIP256
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#endif
#define LEDSTRIPBRIGHTNESS 0.05
#define MINDELAY  120
#define MAXDELAY  180
#endif

#ifdef OLED
NGColorOLED *cdm = new NGColorOLED();
#endif
#ifdef DOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#else
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif

NGColorDotMatrixEffectStarLights *effect = new NGColorDotMatrixEffectStarLights(cdm);

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm->initialize();
  #endif
  effect->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
}

void loop() {
  effect->processingLoop();
}
