#include <NGEngineCore.h>
#include <Visuals/NGTFTDisplay.h>

#define TFTVERTICALSWITCH 42

#define DELAY 10000

NGTFTDisplay tft = NGTFTDisplay();

void setup() {
  observeMemory(0);
  if (IsSwitchOn(TFTVERTICALSWITCH)) {
    tft.setDisplayDirection(tddVertical);
    Serial.println("TFT vertical");
  } else {
    tft.setDisplayDirection(tddHorizontal);
    Serial.println("TFT horizontal");    
  }
  tft.initialize();
  char log[100];
  sprintf(log, "TFT-Width: %d, TFT-Height %d", tft.getWidth(), tft.getHeight());
  Serial.println(log);
  tft.testSequenceStart();
  delay(DELAY);
  tft.testSequenceStop();
  observeMemory(0);
}

void loop() {

}