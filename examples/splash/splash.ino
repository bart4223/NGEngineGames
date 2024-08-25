#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256

#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGColorLEDStrip.h>
#include <NGSplash.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>
#include <NGColorDotMatrixEffectZini.h>

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

#ifdef LEDSTRIP100
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif

#define LOGGING true

bool finished = false;

NGSplash *splash = new NGSplash(new NGSerialNotification());
NGColorDotMatrixEffectRetroRibbons *effectOne = new NGColorDotMatrixEffectRetroRibbons(cdm);
NGColorDotMatrixEffectZini *effectTwo = new NGColorDotMatrixEffectZini(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  splash->setLogging(LOGGING);
  splash->registerEffect(effectOne, 0, 5000);
  splash->registerEffect(effectTwo, 1000, 2000);
  splash->initialize();
  observeMemory(0);
}

void loop() {
  if (!finished) {
    finished = splash->isFinished();
    if (!finished) {
      splash->processingLoop();
    } else {
      splash->writeInfo("Splash finished!");
      cdm->clear();
    }
  }
}
