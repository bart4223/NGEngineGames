#include <NGMemoryObserver.h>
#include <NGColorOLED.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define DELAY 1000

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

byte counter = 0x09;
int posx = 0;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setScale(5);
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  cdmdd->setRandomColor(true);
  //cdmdd->setColor(COLOR_GREEN);
  cdmdd->setPosX(posx);
  cdmdd->setValue(counter);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  posx++;
  cdm->beginUpdate();
  cdm->clear();
  if (counter == 0) {
    counter = 0x09;
  } else {
    counter--;
  }
  cdmdd->setValue(counter);
  cdm->endUpdate();
}
