#include <NGMemoryObserver.h>
#include <NGSoundMachine.h>
#include <NGJingleSuperMarioShort.h>

#define DELAY     10000
#define KEEPALIVE   500

NGSoundMachine sm = NGSoundMachine();

long lastPlay = 0;
long lastKeepAlive = 0;

void setup()
{
  observeMemory(0);
  sm.setConcurrently(true);
  sm.registerJingle(new NGJingleSuperMarioShort);
  sm.initialize();
  observeMemory(0);
}

void loop()
{
  if (millis() - lastPlay > DELAY || lastPlay == 0) {
    Serial.println("Fire sound playing");
    sm.playRandom();
    Serial.println("...done");
    lastPlay = millis();
    observeMemory(0);  
  }
  sm.processingLoop();
  if (lastKeepAlive == 0 || millis() - lastKeepAlive > KEEPALIVE) {
    Serial.println("Keep alive");
    lastKeepAlive = millis();
  }
}