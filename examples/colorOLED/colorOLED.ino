#include <NGMemoryObserver.h>
#include <NGColorOLED.h>

#define DELAY 3000

NGColorOLED co = NGColorOLED();

bool color = false;
int colorRed = convertColorRGBToInt(COLOR_RED);
int colorGreen = convertColorRGBToInt(COLOR_GREEN);

void setup() {
  char log[100];
  observeMemory(0);
  co.initialize();
  co.clear();
  sprintf(log, "Width: %d Height: %d", co.getWidth(), co.getHeight());
  Serial.println(log);
  observeMemory(0);
}

void loop() {
  co.beginUpdate();
  for (int y = 0; y < co.getHeight(); y++) {
    for (int x = 0; x < co.getWidth(); x++) {
      if (color) {
        co.drawPoint(x, y, colorGreen);
        //co.fillRect(y, x, y, x, COLOR_GREEN);
      } else {
        co.drawPoint(x, y, colorRed);
        //co.fillRect(y, x, y, x, COLOR_RED);
      }
    }
  }
  co.endUpdate();
  color = !color;
  observeMemory(DELAY);
}
