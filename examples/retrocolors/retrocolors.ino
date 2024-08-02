#include <NGMemoryObserver.h>
#include <NGColorLEDStrip.h>
#include <NGColorDotMatrixEffectRetroColors.h>

#define LEDSTRIPPIN           6
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#define LEDSTRIPBRIGHTNESS 0.05

NGColorLEDStrip *cdm = new NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);

NGColorDotMatrixEffectRetroColors *rc = new NGColorDotMatrixEffectRetroColors(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  observeMemory(0);
}

void loop() {
  rc->processingLoop();
}
