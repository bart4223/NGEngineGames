#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGColorDotMatrixBinaryDigit.h>
#include <NGSpriteHeart.h>

#define DELAY 1000
#define SCALE    8

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixBinaryDigit *bd = new NGColorDotMatrixBinaryDigit(cdm, 4, bddUp, 0, 7);

byte lives = 15;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setBackground(COLOR_BLACK);
  cdm->setScale(SCALE);
  cdm->clear();
  bd->registerPaintableObjectOn(new NGSpriteHeart(cdm));
  bd->setColorOn(COLOR_RED);
  bd->setValue(lives);
  observeMemory(0);
}

void loop() {
  observeMemory(DELAY);
  if (lives == 0) {
    lives = 15;
  } else {
    lives--;
  }
  bd->setValue(lives);
}
