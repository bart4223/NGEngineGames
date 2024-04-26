#define C64 // ZX81, ZXSPECTRUM, C64

#include <NGMemoryObserver.h>
#ifdef ZX81
#include <NGZX81Font.h>
#endif
#ifdef ZXSPECTRUM
#include <NGZXSpectrumFont.h>
#endif
#ifdef C64
#include <NGC64Font.h>
#endif
#include <NGColorOLED.h>
#include <NGColorDotMatrixDecimalDigit.h>

#define DELAY   500

#ifdef ZX81
#define SCALE 2
NGZX81Font *font = new NGZX81Font();
#endif
#ifdef ZXSPECTRUM
#define SCALE 2
NGZXSpectrumFont *font = new NGZXSpectrumFont();
#endif
#ifdef C64
#define SCALE 2
NGC64Font *font = new NGC64Font();
#endif

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixDecimalDigit *cdmdd = new NGColorDotMatrixDecimalDigit(cdm);

#define START 0x09

byte counter = START;
int posx = 0;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
  //cdmdd->setRandomColorBackground(true);
  //cdmdd->setColorBackground(COLOR_RED);
  //cdmdd->setRandomColor(true);
  #ifdef ZXSPECTRUM
  cdmdd->setColor(COLOR_WHITE);
  #endif
  #ifdef C64
  cdmdd->setColor(COLOR_BLUE);
  #endif
  cdmdd->setFont(font);
  cdmdd->setPosX(posx);
  cdmdd->setValue(counter);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  cdm->beginUpdate();
  cdm->clear();
  if (counter == 0) {
    counter = START;
  } else {
    counter--;
  }
  cdmdd->setValue(counter);
  cdm->endUpdate();
}
