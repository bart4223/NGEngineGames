#define OLED //OLED, DOTMATRIX

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
#define MINDELAY   40
#define MAXDELAY  160
#endif
#ifdef DOTMATRIX
#define SCALE      1
#define MINDELAY   6
#define MAXDELAY  16
#endif
#define MINGRADIENTSTAGES   6
#define MAXGRADIENTSTAGES  12

#ifdef OLED
NGColorOLED *cdm = new NGColorOLED();
#endif
#ifdef DOTMATRIX
NGColorDotMatrix *cdm = new NGColorDotMatrix();
#endif
NGColorDotMatrixEffectZini *ziniOne;
NGColorDotMatrixEffectZini *ziniTwo;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A0);
  ziniOne = new NGColorDotMatrixEffectZini(cdm, getRandomColor(), random(MINGRADIENTSTAGES, MAXGRADIENTSTAGES + 1), random(MINDELAY, MAXDELAY));
  ziniTwo = new NGColorDotMatrixEffectZini(cdm, getRandomColor(), random(MINGRADIENTSTAGES, MAXGRADIENTSTAGES + 1), random(MINDELAY, MAXDELAY));
  #ifdef OLED
  ziniOne->setRandomDelay(false);
  ziniTwo->setRandomDelay(false);
  #endif
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
}

void loop() {
  ziniOne->processingLoop();
  ziniTwo->processingLoop();
}
