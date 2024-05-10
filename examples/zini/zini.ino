#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGColorDotMatrixEffectZini.h>
#include <NGColorDotMatrix.h>

#define MAXGRADIENTSTAGES  12
#define MAXDELAY           16

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGColorDotMatrixEffectZini *ziniOne;
NGColorDotMatrixEffectZini *ziniTwo;

void setup() {
  observeMemory(0);
  initGlobalRandomSeedWithAnalogInput(A0);
  ziniOne = new NGColorDotMatrixEffectZini(cdm, getRandomColor(), random(6, MAXGRADIENTSTAGES + 1), random(6, MAXDELAY));
  ziniTwo = new NGColorDotMatrixEffectZini(cdm, getRandomColor(), random(6, MAXGRADIENTSTAGES + 1), random(6, MAXDELAY));
  cdm->initialize();
}

void loop() {
  ziniOne->processingLoop();
  ziniTwo->processingLoop();
}
