#define PROD false //false, true

#include <NGEngineGames.h>

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {

}