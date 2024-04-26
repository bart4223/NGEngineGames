#include <NGMemoryObserver.h>
#include <NGZX81Font.h>
#include <NGZXSpectrumFont.h>
#include <NGC64Font.h>
#include <NGColorOLED.h>
#include <NGColorDotMatrixText.h>

#define DELAY 5000

NGZX81Font *fontZX81 = new NGZX81Font();
NGZXSpectrumFont *fontZXSpectrum = new NGZXSpectrumFont();
NGC64Font *fontC64 = new NGC64Font();

NGColorOLED *cdm = new NGColorOLED();
NGColorDotMatrixText *cdmt = new NGColorDotMatrixText(cdm);

#define START 0x00
#define MAX   0x02

byte step = START;

void setup() {
  observeMemory(0);
  cdm->initialize();
  cdm->clear();
  cdmt->setWrapText(true);
  observeMemory(0);
}

void loop() {
  delay(DELAY);
  switch(step) {
    case 0x00:
      cdm->setBackground(COLOR_WHITE);
      cdm->setScale(1);
      break;
    case 0x01:
      cdm->setBackground(COLOR_WHITE);
      cdm->setScale(1);
      break;
    case 0x02:
      cdm->setScale(1);
      cdm->setBackground(COLOR_BLUE_C64_LOW);
      break;
  }
  cdm->beginUpdate();
  cdm->clear();
  switch(step) {
    case 0x00:
      cdmt->setColorBackground(COLOR_WHITE);
      cdmt->setColor(COLOR_BLACK);
      cdmt->setFont(fontZX81);
      cdmt->setText("ZX81");
      break;
    case 0x01:
      cdmt->setColorBackground(COLOR_WHITE);
      cdmt->setColor(COLOR_BLACK);
      cdmt->setFont(fontZXSpectrum);
      cdmt->setText("© 1982 Sinclair Research Ltd");
      break;
    case 0x02:
      cdmt->setColorBackground(COLOR_BLUE_C64_LOW);
      cdmt->setColor(COLOR_BLUE_C64);
      cdmt->setFont(fontC64);
      cdmt->setText("COMMODORE 64");
      break;
  };
  step++;
  if (step > MAX) {
    step = START;
  }
  cdm->endUpdate();
}
