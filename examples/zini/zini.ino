#define OLED //OLED, DOTMATRIX
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
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
}

void loop() {
  ziniOne->processingLoop();
  ziniTwo->processingLoop();
}
