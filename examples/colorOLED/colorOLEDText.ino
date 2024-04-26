#include <NGMemoryObserver.h>
#include <NGZXSpectrumFont.h>
#include <NGColorOLED.h>
#include <NGColorDotMatrixText.h>

#define SCALE     1
#define DELAY  5000

NGZXSpectrumFont *fontZXSpectrum = new NGZXSpectrumFont();

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixText *cdmt = new NGColorDotMatrixText(cdm);

#define START 0x00
#define MAX   0x01

byte step = START;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->setScale(SCALE);
  cdm->clear();
  cdmt->setColor(COLOR_WHITE);
  cdmt->setFont(fontZXSpectrum);
  cdmt->setWrapText(true);
  //cdmt->setPosX(1);
  //cdmt->setPosY(1);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  cdm->beginUpdate();
  cdm->clear();
  switch(step) {
    case 0x00:
      cdmt->setColor(COLOR_YELLOW);
      cdmt->setText("ZX81");
      break;
    case 0x01:
      cdmt->setColor(COLOR_WHITE);
      cdmt->setText("© 1982 Sinclair Research Ltd");
      break;
  };
  step++;
  if (step > MAX) {
    step = START;
  }
  cdm->endUpdate();
}
