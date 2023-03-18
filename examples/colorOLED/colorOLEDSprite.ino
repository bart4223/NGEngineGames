#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGSpriteDirt.h>
#include <NGSpriteHeart.h>
#include <NGSpriteRocky.h>
#include <NGSpriteDiamond.h>

#define DELAY 3000
#define SCALE    1

NGColorOLED *cdm = new NGColorOLED();
//NGCustomSprite *sprite = new NGSpriteDirt(cdm);
//NGCustomSprite *sprite = new NGSpriteHeart(cdm);
//NGCustomSprite *sprite = new NGSpriteRocky(cdm);
NGCustomSprite *sprite = new NGSpriteDiamond(cdm);

long _lastToggle = 0;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setBackground(COLOR_DARKGRAY);
  cdm->clear();
  sprite->setScale(SCALE);
  sprite->setTransparent(true);
  observeMemory(0);
}

void loop() {
  for (int y = 0; y < 8 / sprite->getScale() ; y++) {
    for (int x = 0; x < 8 / sprite->getScale(); x++) {
      sprite->setPosition(x * sprite->getWidth(), y * sprite->getHeight());
    }
  }
  //cdm->drawPoint(1, 1, COLOR_GREEN);
  if (millis() - _lastToggle > DELAY) {
    observeMemory(0);
    //sprite->setTransparent(!sprite->getTransparent());
    //cdm->clear();
    _lastToggle = millis();
  }
}
