#define PROD false    //false, true
#define LEDSTRIP100   //LEDSTRIP100, LEDSTRIP256
 
// Game "Dot"
//#define GAME1
// Game "Snake"
//#define GAME2
// Game "Asteroids"
//#define GAME3
// Game "Tetris"
#define GAME4
// Game "Boulderdash"
//#define GAME5

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGColorLEDStrip.h>
#include <NGGameMachineUnitControl.h>
#include <NGJingleBoot.h>
#include <NGJingleSuperMarioShort.h>
#include <NGPaintableComponentEffectVoid.h>
#include <NGColorDotMatrixEffectRetroRibbons.h>
#include <NGColorDotMatrixEffectText.h>
#include <NGSoundMachineEffect.h>
#include <NGColorDotMatrixEffectStarLights.h>
#include <NGColorDotMatrixEffectZini.h>
#include <NGZX81Font.h>

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

#define LEDSTRIPPIN           8
#define LEDSTRIPBRIGHTNESS 0.05
#ifdef LEDSTRIP100
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#endif
#ifdef LEDSTRIP256
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#endif

#define _GAMEMACHINE  "Ardcade"
#define GAMEMACHINE   (char*)_GAMEMACHINE

#define BUTTONA_PINACTIVATION  22
#define BUTTONA_PIN            23
#define BUTTONA_ID           0x2A
#define BUTTONB_PINACTIVATION  24
#define BUTTONB_PIN            25
#define BUTTONB_ID           0x2B

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

#define SOUNDACTIVATIONPIN 9

#define GAMEMACHINESTARTCOLOR     COLOR_BLUE_C64_LOW
#define GAMEMACHINESTARTCOLORDONE COLOR_BLACK

NGSimpleKeypad simpleKeypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine(DEFPINPIEZO, SOUNDACTIVATIONPIN);
NGSerialNotification serialNotification = NGSerialNotification();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINXL, JOYSTICKPINXR, JOYSTICKPINYD, JOYSTICKPINYU, BUTTONB_PIN, true);
#if (PROD == false)
NGSplash splash = NGSplash(&serialNotification);
#else
NGSplash splash = NGSplash();
#endif
#ifdef LEDSTRIP100
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#endif

NGColorDotMatrixEffectRetroRibbons *effectOne = new NGColorDotMatrixEffectRetroRibbons(&cdm);
NGZX81Font *fontZX81 = new NGZX81Font();
NGColorDotMatrixEffectText *effectThree = new NGColorDotMatrixEffectText(&cdm, COLOR_BLUE, COLOR_TRANSPARENT, fontZX81);
NGPaintableComponentEffectVoid *effectFour = new NGPaintableComponentEffectVoid(&cdm);
NGSoundMachineEffect *effectTwo = new NGSoundMachineEffect(&soundMachine);

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

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
  initGlobalRandomSeedWithAnalogInput(A15);
  // ColorDotMatrix
  cdm.initialize(LEDSTRIPBRIGHTNESS);
  cdm.setBackground(GAMEMACHINESTARTCOLOR);
  cdm.clear();
  cdm.setBackground(GAMEMACHINESTARTCOLORDONE);
  // Sound
  int jingleBoot = soundMachine.registerJingle(new NGJingleBoot);
  int jingleStartup = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.setConcurrently(true);
  soundMachine.initialize();
  soundMachine.activate();
  // Splash
  splash.registerPaintableComponent(&cdm);
  splash.registerEffect(effectOne, 500, 2900);
  effectTwo->playJingle(jingleBoot);
  splash.registerEffect(effectTwo, 0, 1500);
  effectThree->setPosition((cdm.getWidth() - 8) / 2, (cdm.getHeight() - 8) / 2);
  effectThree->setDelay(200);
  effectThree->setText("ARDCADE");
  splash.registerEffect(effectThree, 1500, 1400);
  splash.registerEffect(effectFour, 3400, 10);
  // GameMachine
  setGlobalUnit(&unitGameMachine);
  unitGameMachine.registerSplash(&splash);
  switch(random(0, 2)) {
    case 0:
      unitGameMachine.registerEffectIdle(new NGColorDotMatrixEffectStarLights(&cdm));
      break;
    case 1:
      unitGameMachine.registerEffectIdle(new NGColorDotMatrixEffectZini(&cdm, getRandomColor(), random(ZINIMINGRADIENTSTAGES, ZINIMAXGRADIENTSTAGES + 1), random(ZINIMINDELAY, ZINIMAXDELAY)));
      break;
  }
  #if (PROD == false)
  unitGameMachine.registerNotification(&serialNotification);
  unitGameMachine.setLogging(true);
  #else
  unitGameMachine.setLogging(false);
  #endif
  unitGameMachine.initialize();
  // Keypad
  simpleKeypad.registerCallback(&SimpleKeypadCallback);
  simpleKeypad.registerKey(BUTTONA_PIN, BUTTONA_PINACTIVATION, BUTTONA_ID, KEYDELAY, skmHigh);
  simpleKeypad.registerKey(BUTTONB_PIN, BUTTONB_PINACTIVATION, BUTTONB_ID, KEYDELAY, skmHigh);
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
  game.registerColorDotMatrix(&cdm);
  #endif
  // Game "Two"
  #ifdef GAME2
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&cdm);
  #endif
  // Game "Three"
  #ifdef GAME3
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME4
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME5
  game.registerGameKey(gfStartGame, BUTTONA_ID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&cdm);
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
    case BUTTONA_ID:
      simpleKeypad.deactivateKey(BUTTONA_ID);
      unitGameMachine.startGame();
      break;
  }
  #if (PROD == false)
  observeMemory(0);
  #endif
}
