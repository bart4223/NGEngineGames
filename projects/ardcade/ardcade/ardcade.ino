#define PROD false     //false, true
#define LEDSTRIP       //OLED, DOTMATRIX, LEDSTRIP
#define LEDSTRIP256    //LEDSTRIP100, LEDSTRIP256
#define JOYSTICKANALOG //JOYSTICKANALOG, JOYSTICKDIGITAL
 
// Game "Dot"
//#define GAME1
// Game "Snake"
//#define GAME2
// Game "Asteroids"
//#define GAME3
// Game "Tetris"
//#define GAME4
// Game "Boulderdash"
#define GAME5

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGJingleHelloDude.h>
#include <NGJingleSuperMarioShort.h>
#include <NGSerialNotification.h>
#include <NGGameMachineUnitControl.h>
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
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef LEDSTRIP
#include <NGColorLEDStrip.h>
#define LEDSTRIPPIN           6
#ifdef LEDSTRIP100
#define LEDSTRIPPIXELS      100
#define LEDSTRIPROWS         10
#endif
#ifdef LEDSTRIP256
#define LEDSTRIPPIXELS      256
#define LEDSTRIPROWS         16
#endif
#define LEDSTRIPBRIGHTNESS 0.05
#endif

#define _GAMEMACHINE  "Ardcade"
#define GAMEMACHINE   (char*)_GAMEMACHINE

#define STARTGAMEPIN        12
#define STARTGAMEID         0x2A
#define TOGGLESOUNDPIN      11
#define TOGGLESOUND         0x2B

#define KEYDELAY      500
#define JOYSTICKDELAY 100

#define JOYSTICKID       0
#ifdef JOYSTICKANALOG
#define JOYSTICKPINX    A0
#define JOYSTICKPINY    A1
#endif
#ifdef JOYSTICKDIGITAL
#define JOYSTICKPINXL    4
#define JOYSTICKPINXR    5
#define JOYSTICKPINYD    7
#define JOYSTICKPINYU    6
#endif
#define JOYSTICKPINFIRE  8

#define JOYSTICKTHRESHOLDUP       200
#define JOYSTICKTHRESHOLDDOWN     823
#define JOYSTICKTHRESHOLDLEFT     200
#define JOYSTICKTHRESHOLDRIGHT    823

NGSimpleKeypad simpleKeypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine();
NGSerialNotification serialNotification = NGSerialNotification();
#ifdef JOYSTICKANALOG
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#endif
#ifdef JOYSTICKDIGITAL
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINXL, JOYSTICKPINXR, JOYSTICKPINYD, JOYSTICKPINYU, JOYSTICKPINFIRE);
#endif
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
#ifdef LEDSTRIP256
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS, lskUpDownAlternate);
#else
NGColorLEDStrip cdm = NGColorLEDStrip(LEDSTRIPPIN, LEDSTRIPPIXELS, LEDSTRIPROWS);
#endif
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
  // GameMachine
  setGlobalUnit(&unitGameMachine);
  #if (PROD == false)
  unitGameMachine.registerNotification(&serialNotification);
  unitGameMachine.setLogging(true);
  #else
  unitGameMachine.setLogging(false);
  #endif
  // ColorDotMatrix
  #ifdef LEDSTRIP
  cdm.initialize(LEDSTRIPBRIGHTNESS);
  #else
  cdm.initialize();
  #endif
  #ifdef OLED
  cdm.setScale(8);
  #endif
  cdm.clear();
  unitGameMachine.initialize();
  // Keypad
  simpleKeypad.registerCallback(&SimpleKeypadCallback);
  simpleKeypad.registerKey(STARTGAMEPIN, STARTGAMEID, KEYDELAY);
  simpleKeypad.registerKey(TOGGLESOUNDPIN, TOGGLESOUND, KEYDELAY);
  simpleKeypad.initialize();
  // Joystick
  #ifdef GAME3
  joystick.setContinuousFireThreshold(CONTINOUSFIRETHRESHOLD);
  #endif
  joystick.registerAction(jaX, jtkLess, JOYSTICKTHRESHOLDLEFT, JOYSTICKDELAY, jmLeft);
  joystick.registerAction(jaX, jtkGreater, JOYSTICKTHRESHOLDRIGHT, JOYSTICKDELAY, jmRight);
  joystick.registerAction(jaY, jtkLess, JOYSTICKTHRESHOLDUP, JOYSTICKDELAY, jmUp);
  joystick.registerAction(jaY, jtkGreater, JOYSTICKTHRESHOLDDOWN, JOYSTICKDELAY, jmDown);
  joystick.registerAction(JOYSTICKPINFIRE, jamTriggerLOW, JOYSTICKDELAY, jmFire);
  // Sound
  int jingleStart = soundMachine.registerJingle(new NGJingleHelloDude());
  int jingleStartUp = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.initialize();
  // Game "One"
  #ifdef GAME1
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartUp);
  game.registerSoundStart(jingleStart);
  game.registerColorDotMatrix(&cdm);
  #endif
  // Game "Two"
  #ifdef GAME2
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartUp);
  game.registerSoundStart(jingleStart);
  game.registerColorDotMatrix(&cdm);
  #endif
  // Game "Three"
  #ifdef GAME3
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartUp);
  game.registerSoundStart(jingleStart);
  game.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME4
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartUp);
  game.registerSoundStart(jingleStart);
  game.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME5
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartUp);
  game.registerSoundStart(jingleStart);
  game.registerColorDotMatrix(&cdm);
  #endif
  // Init
  #if (PROD == true)
  unitGameMachine.setWorkMode(wmNone);
  #else
  unitGameMachine.setWorkMode(wmObserveMemory);
  unitGameMachine.toggleDoPlaySound();
  #endif
  unitGameMachine.startUp();
  unitGameMachine.clearInfo();
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {
  soundMachine.processingLoop();
  simpleKeypad.processingLoop();
  unitGameMachine.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  switch(id) {
    case STARTGAMEID:
      unitGameMachine.startGame();
      break;
    case TOGGLESOUND:
      unitGameMachine.toggleDoPlaySound();
      break;
  }
  #if (PROD == false)
  observeMemory(0);
  #endif
}
}
