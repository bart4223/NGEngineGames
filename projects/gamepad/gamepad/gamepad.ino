#define PROD false //false, true

#include <NGMemoryObserver.h>
#include <NGSerialNotification.h>
#include <NGGamePad.h>

NGGamePad gamepad = NGGamePad();

void setup() {
  observeMemory(0);
  #if (PROD == false)
  gamepad.setLogging(true);
  gamepad.registerNotification(new NGSerialNotification());
  #endif
  gamepad.initialize();
  observeMemory(0);
}

void loop() {

}
