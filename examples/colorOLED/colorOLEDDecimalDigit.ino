#include <NGMemoryObserver.h>
#include <NGZX81Font.h>
#include <NGColorOLED.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define SCALE     3
#define DELAY   500

NGZX81Font *fontZX81 = new NGZX81Font();

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

byte counter = 0x09;
int posx = 0;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  //cdmdd->setRandomColor(true);
  //cdmdd->setColor(COLOR_GREEN);
  cdmdd->setFont(fontZX81);
  cdmdd->setPosX(posx);
  cdmdd->setValue(counter);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
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
