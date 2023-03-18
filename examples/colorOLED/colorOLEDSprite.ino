#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGSpriteDirt.h>
#include <NGSpriteHeart.h>

#define DELAY 3000
#define SCALE    1

NGColorOLED *cdm = new NGColorOLED();
//NGCustomSprite *sprite = new NGSpriteDirt(cdm);
NGCustomSprite *sprite = new NGSpriteHeart(cdm);

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setBackground(COLOR_DARKGRAY);
  cdm->clear();
  sprite->setScale(SCALE);
  //sprite->setTransparent(true);
  observeMemory(0);
}

void loop() {
  for (int y = 0; y < 8 / sprite->getScale() ; y++) {
    for (int x = 0; x < 8 / sprite->getScale(); x++) {
      sprite->setPosition(x * sprite->getWidth(), y * sprite->getHeight());
    }
  }
  //cdm->drawPoint(1, 1, COLOR_GREEN);
  observeMemory(DELAY);
  sprite->setTransparent(!sprite->getTransparent());
  cdm->clear();
}
