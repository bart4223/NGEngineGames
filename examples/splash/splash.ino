#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256

#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGColorLEDStrip.h>
#include <NGSplash.h>
#include <NGPaintableComponentEffectVoid.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>
#include <NGColorDotMatrixEffectZini.h>
#include <NGColorDotMatrixEffectText.h>
#include <NGZX81Font.h>

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
//NGColorDotMatrixEffectZini *effectTwo = new NGColorDotMatrixEffectZini(cdm);
NGZX81Font *fontZX81 = new NGZX81Font();
NGColorDotMatrixEffectText *effectThree = new NGColorDotMatrixEffectText(cdm, COLOR_BLUE, COLOR_TRANSPARENT, fontZX81);
NGPaintableComponentEffectVoid *effectFour = new NGPaintableComponentEffectVoid(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  splash->setLogging(LOGGING);
  splash->registerEffect(effectOne, 0, 2400);
  //splash->registerEffect(effectTwo, 1000, 2000);
  effectThree->setPosition((cdm->getWidth() - 8) / 2, (cdm->getHeight() - 8) / 2);
  effectThree->setDelay(200);
  effectThree->setText("ARDCADE");
  splash->registerEffect(effectThree, 500, 1400);
  splash->registerEffect(effectFour, 2400, 10);
  splash->initialize();
  observeMemory(0);
}

void loop() {
  if (!finished) {
    finished = splash->isFinished();
    if (!finished) {
      cdm->beginUpdate();
      splash->processingLoop();
      cdm->endUpdate();
    } else {
      splash->writeInfo("Splash finished!");
    }
  }
}
