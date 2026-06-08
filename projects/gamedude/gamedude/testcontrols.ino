#include <NGEngineCore.h>

#define KEYSELECTPIN  12
#define KEYSELECTID   42
#define KEYSTARTPIN   11
#define KEYSTARTID    43
#define KEYAPIN        6
#define KEYAID        44
#define KEYBPIN        7
#define KEYBID        45
#define KEYUPPIN       2
#define KEYUPID       46
#define KEYDOWNPIN     3
#define KEYDOWNID     47
#define KEYLEFTPIN     4
#define KEYLEFTID     48
#define KEYRIGHTPIN    5
#define KEYRIGHTID    49

#define DELAY 500

NGSimpleKeypad skpMain = NGSimpleKeypad();
NGSimpleKeypad skpControl = NGSimpleKeypad();

void setup() {
  observeMemory(0);
  skpMain.registerCallback(&KeypadCallback);
  skpMain.registerKey(KEYSELECTPIN, KEYSELECTID, DELAY);
  skpMain.registerKey(KEYSTARTPIN, KEYSTARTID, DELAY);
  skpMain.registerKey(KEYAPIN, KEYAID, DELAY);
  skpMain.registerKey(KEYBPIN, KEYBID, DELAY);
  skpMain.initialize();
  skpControl.registerCallback(&KeypadCallback);
  skpControl.registerKey(KEYUPPIN, KEYUPID, DELAY);
  skpControl.registerKey(KEYDOWNPIN, KEYDOWNID, DELAY);
  skpControl.registerKey(KEYLEFTPIN, KEYLEFTID, DELAY);
  skpControl.registerKey(KEYRIGHTPIN, KEYRIGHTID, DELAY);
  skpControl.initialize();
  observeMemory(0);
}

void loop() {
  skpMain.processingLoop();
  skpControl.processingLoop();
}

void KeypadCallback(byte id) {
  switch(id) {
    case KEYSELECTID:
      Serial.println("Press SELECT");
      break;
    case KEYSTARTID:
      Serial.println("Press START");
      break;
    case KEYAID:
      Serial.println("Press A");
      break;
    case KEYBID:
      Serial.println("Press B");
      break;
    case KEYUPID:
      Serial.println("Press UP");
      break;
    case KEYDOWNID:
      Serial.println("Press DOWN");
      break;
    case KEYLEFTID:
      Serial.println("Press LEFT");
      break;
    case KEYRIGHTID:
      Serial.println("Press RIGHT");
      break;
  }
}
