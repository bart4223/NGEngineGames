#define LEDSTRIP    //OLED, DOTMATRIX, LEDSTRIP
#define LEDSTRIP256 //LEDSTRIP100, LEDSTRIP256
//#define RANDOMCOLOR

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#include <NGColorDotMatrixEffectZini.h>

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
#define LEDSTRIPPIN 6
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

#define MINGRADIENTSTAGES   6
#define MAXGRADIENTSTAGES  12

NGColorDotMatrixEffectZini *ziniOne;
NGColorDotMatrixEffectZini *ziniTwo;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A5);
  colorRGB colorZiniOne;
  colorRGB colorZiniTwo;
  #ifdef RANDOMCOLOR
  colorZiniOne = getRandomColor();
  colorZiniTwo = getRandomColor();
  #else
  colorZiniOne = COLOR_GREEN;
  colorZiniTwo = COLOR_YELLOW;
  #endif
  ziniOne = new NGColorDotMatrixEffectZini(cdm, colorZiniOne, random(MINGRADIENTSTAGES, MAXGRADIENTSTAGES + 1), random(MINDELAY, MAXDELAY));
  ziniTwo = new NGColorDotMatrixEffectZini(cdm, colorZiniTwo, random(MINGRADIENTSTAGES, MAXGRADIENTSTAGES + 1), random(MINDELAY, MAXDELAY));
  #ifdef OLED
  ziniOne->setRandomDelay(false);
  ziniTwo->setRandomDelay(false);
  #endif
  #ifdef LEDSTRIP
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm->initialize();
  #endif
  cdm->setScale(SCALE);
  cdm->clear();
}

void loop() {
  ziniOne->processingLoop();
  ziniTwo->processingLoop();
}
