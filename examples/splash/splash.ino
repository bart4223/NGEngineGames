#define LEDSTRIP100 //LEDSTRIP100, LEDSTRIP256

#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGColorLEDStrip.h>
#include <NGSplash.h>
#include <NGPaintableComponentEffectVoid.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>
#include <NGColorDotMatrixEffectText.h>
#include <NGSoundMachineEffect.h>
#include <NGJingleBoot.h>
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

#define ACTIVATIONPIN 9

#define LOGGING true

bool finished = false;

NGSoundMachine *sm = new NGSoundMachine(DEFPINPIEZO, ACTIVATIONPIN);
NGSplash *splash = new NGSplash(new NGSerialNotification());
NGColorDotMatrixEffectRetroRibbons *effectOne = new NGColorDotMatrixEffectRetroRibbons(cdm);
NGZX81Font *fontZX81 = new NGZX81Font();
NGColorDotMatrixEffectText *effectThree = new NGColorDotMatrixEffectText(cdm, COLOR_BLUE, COLOR_TRANSPARENT, fontZX81);
NGPaintableComponentEffectVoid *effectFour = new NGPaintableComponentEffectVoid(cdm);
NGSoundMachineEffect *effectTwo = new NGSoundMachineEffect(sm);

void setup() {
  observeMemory(0);
  sm->setConcurrently(true);
  sm->initialize();
  cdm->initialize(LEDSTRIPBRIGHTNESS);
  splash->setLogging(LOGGING);
  splash->registerPaintableComponent(cdm);
  splash->registerEffect(effectOne, 500, 2900);
  effectTwo->playJingle(sm->registerJingle(new NGJingleBoot));
  splash->registerEffect(effectTwo, 0, 1500);
  effectThree->setPosition((cdm->getWidth() - 8) / 2, (cdm->getHeight() - 8) / 2);
  effectThree->setDelay(200);
  effectThree->setText("ARDCADE");
  splash->registerEffect(effectThree, 1500, 1400);
  splash->registerEffect(effectFour, 3400, 10);
  splash->initialize();
  sm->activate();
  sm->play(0);
  observeMemory(0);
}

void loop() {
  if (!finished) {
    finished = splash->isFinished();
    if (!finished) {
      splash->processingLoop();
    } else {
      splash->writeInfo("Splash finished!");
    }
  }
}
