#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGColorLEDStrip.h>
#include <NGSplash.h>
#include <NGColorDotMatrixEffectRetroColors.h>
#include <NGColorDotMatrixEffectZini.h>

#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#define LEDSTRIPBRIGHTNESS 0.05

NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);

NGSplash *splash = new NGSplash(new NGSerialNotification());
NGColorDotMatrixEffectRetroColors *effectOne = new NGColorDotMatrixEffectRetroColors(cdm);
NGColorDotMatrixEffectZini *effectTwo = new NGColorDotMatrixEffectZini(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  splash->registerEffect(effectOne);
  splash->registerEffect(effectTwo);
  splash->initialize();
  observeMemory(0);
}

void loop() {
  splash->processingLoop();
}
