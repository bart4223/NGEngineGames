#define PROD true  //false, true
#define NOXMAS //NOXMAS, XMAS
 
// Game "Dot"
//#define GAME1
// Game "Snake"
#define GAME2
// Game "Asteroids"
//#define GAME3
// Game "Tetris"
//#define GAME4
// Game "Boulderdash"
//#define GAME5

#include <NGEngineCore.h>
#include <NGSerialNotification.h>
#include <NGLCDNotification.h>
#include <Visuals/NGColorLEDStrip.h>
#include <NGGameMachineUnitControl.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleAlarm.h>
#include <NGJingleSuperMarioShort.h>
#include <NGDigitalPotentiometer.h>
#include <NGPaintableComponentEffectVoid.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>
#include <NGColorDotMatrixEffectText.h>
#include <NGSoundMachineEffect.h>
#include <NGColorDotMatrixEffectStarLights.h>
#include <NGColorDotMatrixEffectZini.h>
#include <NGColorDotMatrixEffectSnowfall.h>

#ifdef GAME1
#include <NGColorDotMatrixGameDot.h>
#endif
#ifdef GAME2
#include <NGColorDotMatrixGameSnake.h>
#endif
#ifdef GAME3
#include <NGColorDotMatrixGameAsteroids.h>
#endif
#ifdef GAME4
#include <NGColorDotMatrixGameTetris.h>
#endif
#ifdef GAME5
#include <NGColorDotMatrixGameBoulderdash.h>
#endif

#define PINLEDSTRIP                  8
#define PINAUTODETECTIONDISPLAYONE  A0
#define PINAUTODETECTIONDISPLAYTWO  A1
#define DISPLAYTWO_INDICATOR       900
#define DISPLAY_INDICATOR_RANGE     49

#define LEDSTRIP100_INDICATOR   900
#define LEDSTRIP100_PIXELS      100
#define LEDSTRIP100_ROWS         10
#define LEDSTRIP256_INDICATOR   800
#define LEDSTRIP256_PIXELS      256
#define LEDSTRIP256_ROWS         16

#define LEDSTRIPBRIGHTNESS     0.05

#define _GAMEMACHINE  "Ardcade"
#define GAMEMACHINE   (char*)_GAMEMACHINE

#define BUTTONA_PINACTIVATION   22
#define BUTTONA_PIN             23
#define BUTTONA_ID            0x2A
#define BUTTONB_PINACTIVATION   24
#define BUTTONB_PIN             25
#define BUTTONB_ID            0x2B

#define KEYBEEPPIN            26
#define KEYBEEPID           0x2C
#define KEYBRIGHTNESSPIN      27
#define KEYBRIGHTNESSID     0x2D

#define KEYDELAY      500
#define JOYSTICKDELAY 100

#define JOYSTICKID       0
#define JOYSTICKPINXL    4
#define JOYSTICKPINXR    5
#define JOYSTICKPINYD    7
#define JOYSTICKPINYU    6

#define JOYSTICKTHRESHOLDUP       100
#define JOYSTICKTHRESHOLDDOWN     923
#define JOYSTICKTHRESHOLDLEFT     100
#define JOYSTICKTHRESHOLDRIGHT    923

#define SOUNDACTIVATIONPIN     9
#define ADDRESS_SOUNDPOTI   0x00
#define PIN_CS  53
#define SOUNDPOTI_MAX 255
#define SOUNDPOTI_MIN 225
#define SOUNDPOTI_STEP  5

#define LCDADDRESS    0x27
#define LCDCOLUMNS    16
#define LCDLINES      2

#define GAMEMACHINESTARTCOLOR     COLOR_BLUE_C64_LOW
#define GAMEMACHINESTARTCOLORDONE COLOR_BLACK

NGSimpleKeypad simpleKeypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine(DEFPINPIEZO, SOUNDACTIVATIONPIN);
NGDigitalPotentiometer dpSound = NGDigitalPotentiometer(PIN_CS, ADDRESS_SOUNDPOTI);
NGSerialNotification serialNotification = NGSerialNotification();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINXL, JOYSTICKPINXR, JOYSTICKPINYD, JOYSTICKPINYU, BUTTONB_PIN, true);
#if (PROD == false)
NGSplash splash = NGSplash(&serialNotification);
#else
NGSplash splash = NGSplash();
#endif

// 1K = 100 Pixel
// 2K = 256 Pixel
NGColorLEDStrip displayOne = NGColorLEDStrip(PINLEDSTRIP, PINAUTODETECTIONDISPLAYONE);

NGColorDotMatrixEffectRetroRibbons *effectOne = new NGColorDotMatrixEffectRetroRibbons(&displayOne);
NGZX81Font *fontZX81 = new NGZX81Font();
NGColorDotMatrixEffectText *effectThree = new NGColorDotMatrixEffectText(&displayOne, COLOR_BLUE, COLOR_TRANSPARENT, fontZX81);
NGPaintableComponentEffectVoid *effectFour = new NGPaintableComponentEffectVoid(&displayOne);
NGSoundMachineEffect *effectTwo = new NGSoundMachineEffect(&soundMachine);
NGLCDNotification *displayTwo;

#define ZINIMINGRADIENTSTAGES   6
#define ZINIMAXGRADIENTSTAGES  12
#define ZINIMINDELAY  120
#define ZINIMAXDELAY  180

#ifdef GAME1
NGColorDotMatrixGameDot game = NGColorDotMatrixGameDot();
#endif
#ifdef GAME2
NGColorDotMatrixGameSnake game = NGColorDotMatrixGameSnake();
#endif
#ifdef GAME3
#define CONTINOUSFIRETHRESHOLD  5
NGColorDotMatrixGameAsteroids game = NGColorDotMatrixGameAsteroids();
#endif
#ifdef GAME4
NGColorDotMatrixGameTetris game = NGColorDotMatrixGameTetris();
#endif
#ifdef GAME5
NGColorDotMatrixGameBoulderdash game = NGColorDotMatrixGameBoulderdash();
#endif
NGGameMachineUnitControl unitGameMachine = NGGameMachineUnitControl(GAMEMACHINE, &game);

byte jingleBootID;
byte jingleBeepID;
byte jingleAlarmID;
byte jingleStartup;

bool hasDisplayTwo;

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
  initGlobalRandomSeedWithAnalogInput(A15);
  // DisplayOne
  displayOne.setIndicatorRange(DISPLAY_INDICATOR_RANGE);
  displayOne.registerGeometry(LEDSTRIP100_INDICATOR, LEDSTRIP100_PIXELS, LEDSTRIP100_ROWS);
  displayOne.registerGeometry(LEDSTRIP256_INDICATOR, lskUpDownAlternate, LEDSTRIP256_PIXELS, LEDSTRIP256_ROWS);
  displayOne.initialize(LEDSTRIPBRIGHTNESS);
  displayOne.setBackground(GAMEMACHINESTARTCOLOR);
  displayOne.clear();
  displayOne.setBackground(GAMEMACHINESTARTCOLORDONE);
  // DisplayTwo
  int displayTwoIndicator = analogRead(PINAUTODETECTIONDISPLAYTWO);
  hasDisplayTwo = displayTwoIndicator >= DISPLAYTWO_INDICATOR - DISPLAY_INDICATOR_RANGE && displayTwoIndicator <= DISPLAYTWO_INDICATOR + DISPLAY_INDICATOR_RANGE;
  if (hasDisplayTwo) {
    displayTwo = new NGLCDNotification(LCDADDRESS, LCDCOLUMNS, LCDLINES);
    displayTwo->initialize();
    displayTwo->writeInfo(_GAMEMACHINE, 0, 5);
    #if (PROD == false)
    displayTwo->writeInfo("Test and Debug", 1, 1);
    #endif
  }
  // Sound
  dpSound.setMinValue(SOUNDPOTI_MIN);
  dpSound.setMaxValue(SOUNDPOTI_MAX);
  dpSound.setStepValue(SOUNDPOTI_STEP);
  dpSound.initialize(SOUNDPOTI_MAX);
  jingleBootID = soundMachine.registerJingle(new NGJingleBoot);
  jingleBeepID = soundMachine.registerJingle(new NGJingleBeep);
  jingleAlarmID = soundMachine.registerJingle(new NGJingleAlarm);
  jingleStartup = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.setConcurrently(true);
  soundMachine.initialize();
  soundMachine.activate();
  // Splash
  splash.registerPaintableComponent(&displayOne);
  splash.registerEffect(effectOne, 500, 2900);
  effectTwo->playJingle(jingleBootID);
  splash.registerEffect(effectTwo, 0, 1500);
  effectThree->setPosition((displayOne.getWidth() - 8) / 2, (displayOne.getHeight() - 8) / 2);
  effectThree->setDelay(200);
  effectThree->setText("ARDCADE");
  splash.registerEffect(effectThree, 1500, 1400);
  splash.registerEffect(effectFour, 3400, 10);
  // GameMachine
  setGlobalUnit(&unitGameMachine);
  unitGameMachine.registerSplash(&splash);
  #ifdef XMAS
    unitGameMachine.registerEffectIdle(new NGColorDotMatrixEffectSnowfall(&displayOne));
  #else
  switch(random(0, 2)) {
    case 0:
      unitGameMachine.registerEffectIdle(new NGColorDotMatrixEffectStarLights(&displayOne));
      break;
    case 1:
      unitGameMachine.registerEffectIdle(new NGColorDotMatrixEffectZini(&displayOne, getRandomColor(), random(ZINIMINGRADIENTSTAGES, ZINIMAXGRADIENTSTAGES + 1), random(ZINIMINDELAY, ZINIMAXDELAY)));
      break;
  }
  #endif
  #if (PROD == false)
  if (hasDisplayTwo) {
    unitGameMachine.registerNotification(displayTwo);
  }
  else {
    unitGameMachine.registerNotification(&serialNotification);
  }
  unitGameMachine.setLogging(true);
  #else
  unitGameMachine.setLogging(false);
  #endif
  unitGameMachine.initialize();
  // Keypad
  simpleKeypad.registerCallback(&SimpleKeypadCallback);
  simpleKeypad.registerKey(BUTTONA_PIN, BUTTONA_PINACTIVATION, BUTTONA_ID, KEYDELAY, skmHigh);
  simpleKeypad.registerKey(BUTTONB_PIN, BUTTONB_PINACTIVATION, BUTTONB_ID, KEYDELAY, skmHigh);
  simpleKeypad.registerKey(KEYBEEPPIN, KEYBEEPID, KEYDELAY);
  simpleKeypad.registerKey(KEYBRIGHTNESSPIN, KEYBRIGHTNESSID, KEYDELAY);
  simpleKeypad.initialize();
  // Joystick
  #ifdef GAME3
  joystick.setContinuousFireThreshold(CONTINOUSFIRETHRESHOLD);
  #endif
  joystick.registerAction(jamMappingInvers, jaX, jtkLess, JOYSTICKTHRESHOLDLEFT, JOYSTICKDELAY, jmLeft);
  joystick.registerAction(jamMapping, jaX, jtkGreater, JOYSTICKTHRESHOLDRIGHT, JOYSTICKDELAY, jmRight);
  joystick.registerAction(jamMappingInvers, jaY, jtkLess, JOYSTICKTHRESHOLDUP, JOYSTICKDELAY, jmUp);
  joystick.registerAction(jamMapping, jaY, jtkGreater, JOYSTICKTHRESHOLDDOWN, JOYSTICKDELAY, jmDown);
  joystick.registerAction(jamNone, BUTTONB_PIN, JOYSTICKDELAY, jmFire);
  joystick.initialize();
  // Game "One"
  #ifdef GAME1
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&displayOne);
  #endif
  // Game "Two"
  #ifdef GAME2
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&displayOne);
  #endif
  // Game "Three"
  #ifdef GAME3
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&displayOne);
  #endif
  // Game "Four"
  #ifdef GAME4
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&displayOne);
  #endif
  // Game "Five"
  #ifdef GAME5
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&displayOne);
  #endif
  // Startup
  #if (PROD == true)
  unitGameMachine.setWorkMode(wmNone);
  #else
  unitGameMachine.setWorkMode(wmObserveMemory);
  #endif
  unitGameMachine.setPlayStartUpSoundConcurrently(true);
  unitGameMachine.startUp();
  unitGameMachine.clearInfo();
  simpleKeypad.activateKey(BUTTONA_ID);
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {
  soundMachine.processingLoop();
  simpleKeypad.processingLoop();
  if (unitGameMachine.isGameStarted()) {
    if (!simpleKeypad.isKeyActive(BUTTONB_ID)) {
      simpleKeypad.activateKey(BUTTONB_ID);
    }
  } else {
    if (simpleKeypad.isKeyActive(BUTTONB_ID)) {
      simpleKeypad.deactivateKey(BUTTONB_ID);
    }
  }
  unitGameMachine.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case KEYBEEPID:
      dpSound.changeValue();
      if (dpSound.isMinValue() || dpSound.isMaxValue()) {
        soundMachine.play(jingleAlarmID);
      } else {
        soundMachine.play(jingleBeepID);
      }
      break;
    case KEYBRIGHTNESSID:
      displayOne.changeBrightness();
      if (displayOne.isMinBrightness() || displayOne.isMaxBrightness()) {
        soundMachine.play(jingleAlarmID);
      } else {
        soundMachine.play(jingleBeepID);
      }
      break;
    case BUTTONA_ID:
      simpleKeypad.deactivateKey(BUTTONA_ID);
      unitGameMachine.startGame();
      break;
  }
  #if (PROD == false)
  observeMemory(0);
  #endif
}
