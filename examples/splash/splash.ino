#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <NGSplash.h>
#include <NGColorDotMatrixEffectRetroColors.h>

#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#define LEDSTRIPBRIGHTNESS 0.05

NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);

NGSplash *splash = new NGSplash();
NGColorDotMatrixEffectRetroColors *effectOne = new NGColorDotMatrixEffectRetroColors(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  splash->registerEffect(effectOne);
  splash->initialize();
  observeMemory(0);
}

void loop() {
  splash->processingLoop();
}

