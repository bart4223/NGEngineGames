#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256

#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>

#ifdef LEDSTRIP256
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#endif
#ifdef LEDSTRIP100
#define LEDSTRIPPIN           8
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#endif
#define LEDSTRIPBRIGHTNESS 0.05

#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif

NGColorDotMatrixEffectRetroRibbons *effect = new NGColorDotMatrixEffectRetroRibbons(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  effect->initialize();
  observeMemory(0);
}

void loop() {
  effect->processingLoop();
}
