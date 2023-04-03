#define PROD true //false, true
#define DOTMATRIX //OLED, DOTMATRIX

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
#include <NGJingleHelloDude.h>
#include <NGJingleSuperMarioShort.h>
#include <NGSerialNotification.h>
#include <NGBinaryClockUnitControl.h>
#include <NGGamePad.h>
#include <NGColorDotMatrixGameDot.h>
#include <NGColorDotMatrixGameSnake.h>
#include <NGColorDotMatrixGameAsteroids.h>
#include <NGColorDotMatrixGameTetris.h>
#include <NGColorDotMatrixGameBoulderdash.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define _BINARYCLOCK  "Clock"
#define BINARYCLOCK   (char*)_BINARYCLOCK

#define KEYCLOCKCOLOROFFPIN 8
#define KEYCLOCKCOLOROFFID  0x10
#define KEYCLOCKCOLORONPIN  9
#define KEYCLOCKCOLORONID   0x11
#define GAMEONEPIN          10
#define GAMEONEID           0x00
#define GAMETWOPIN          11
#define GAMETWOID           0x01
#define TOGGLESOUNDPIN      12
#define TOGGLESOUND         0x20

#define KEYDELAY      500
#define JOYSTICKDELAY 100

#define JOYSTICKID       0
#define JOYSTICKPINX    A8
#define JOYSTICKPINY    A9
#define JOYSTICKPINFIRE 14

#define JOYSTICKTHRESHOLDUP       200
#define JOYSTICKTHRESHOLDDOWN     823
#define JOYSTICKTHRESHOLDLEFT     200
#define JOYSTICKTHRESHOLDRIGHT    823

#define STARTGAMEPIN 15
#define STARTGAMEID  42

NGSimpleKeypad choosekeypad = NGSimpleKeypad();
NGSimpleKeypad gamekeypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine();
NGSerialNotification serialNotification = NGSerialNotification();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGBinaryClockUnitControl unitBinaryClock = NGBinaryClockUnitControl(BINARYCLOCK, &cdm);
NGGamePad gamepad = NGGamePad();
#ifdef GAME1
NGColorDotMatrixGameDot gameOne = NGColorDotMatrixGameDot();
#endif
#ifdef GAME2
NGColorDotMatrixGameSnake gameTwo = NGColorDotMatrixGameSnake();
#endif
#ifdef GAME3
NGColorDotMatrixGameAsteroids gameThree = NGColorDotMatrixGameAsteroids();
#endif
#ifdef GAME4
NGColorDotMatrixGameTetris gameFour = NGColorDotMatrixGameTetris();
#endif
#ifdef GAME5
NGColorDotMatrixGameBoulderdash gameFive = NGColorDotMatrixGameBoulderdash();
#endif

colorRGB clockColorOff = COLOR_LIME;
colorRGB clockColorOn = COLOR_BLUE;

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
  // Clock
  setGlobalUnit(&unitBinaryClock);
  #if (PROD == false)
  unitBinaryClock.registerNotification(&serialNotification);
  #endif
  // ColorDotMatrix
  cdm.initialize();
  #ifdef OLED
  cdm.setScale(8);
  #endif
  cdm.clear();
  unitBinaryClock.setColorOff(clockColorOff);
  unitBinaryClock.setColorOn(clockColorOn);
  //unitBinaryClock.setAdjustRTC(true);
  unitBinaryClock.initialize();
  // GamePad
  #if (PROD == false)
  gamepad.setLogging(true);
  gamepad.registerNotification(&serialNotification);
  #endif
  // ChooseKeypad
  choosekeypad.registerCallback(&ChooseKeypadCallback);
  choosekeypad.registerKey(KEYCLOCKCOLOROFFPIN, KEYCLOCKCOLOROFFID, KEYDELAY);
  choosekeypad.registerKey(KEYCLOCKCOLORONPIN, KEYCLOCKCOLORONID, KEYDELAY);
  choosekeypad.registerKey(GAMEONEPIN, GAMEONEID, KEYDELAY);
  choosekeypad.registerKey(GAMETWOPIN, GAMETWOID, KEYDELAY);
  choosekeypad.registerKey(TOGGLESOUNDPIN, TOGGLESOUNDPIN, KEYDELAY);
  choosekeypad.initialize();
  // GameKeypad
  gamekeypad.registerCallback(&GameKeypadCallback);
  gamekeypad.registerKey(STARTGAMEPIN, STARTGAMEID, KEYDELAY);
  gamekeypad.initialize();
  // Joystick
  joystick.registerAction(jaX, jtkLess, JOYSTICKTHRESHOLDLEFT, JOYSTICKDELAY, jmLeft);
  joystick.registerAction(jaX, jtkGreater, JOYSTICKTHRESHOLDRIGHT, JOYSTICKDELAY, jmRight);
  joystick.registerAction(jaY, jtkLess, JOYSTICKTHRESHOLDUP, JOYSTICKDELAY, jmUp);
  joystick.registerAction(jaY, jtkGreater, JOYSTICKTHRESHOLDDOWN, JOYSTICKDELAY, jmDown);
  joystick.registerAction(JOYSTICKDELAY, jmFire);
  // Sound
  int jingleStart = soundMachine.registerJingle(new NGJingleHelloDude());
  int jingleStartUp = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.initialize();
  // Game "One"
  #ifdef GAME1
  gamepad.registerGame(&gameOne);
  gameOne.registerGameKey(gfStartGame, STARTGAMEID);
  gameOne.registerGameJoystick(&joystick);
  gameOne.registerSoundMachine(&soundMachine);
  gameOne.registerSoundStartUp(jingleStartUp);
  gameOne.registerSoundStart(jingleStart);
  gameOne.registerColorDotMatrix(&cdm);
  #endif
  // Game "Two"
  #ifdef GAME2
  gamepad.registerGame(&gameTwo);
  gameTwo.registerGameKey(gfStartGame, STARTGAMEID);
  gameTwo.registerGameJoystick(&joystick);
  gameTwo.registerSoundMachine(&soundMachine);
  gameTwo.registerSoundStartUp(jingleStartUp);
  gameTwo.registerSoundStart(jingleStart);
  gameTwo.registerColorDotMatrix(&cdm);
  #endif
  // Game "Three"
  #ifdef GAME3
  gamepad.registerGame(&gameThree);
  gameThree.registerGameKey(gfStartGame, STARTGAMEID);
  gameThree.registerGameJoystick(&joystick);
  gameThree.registerSoundMachine(&soundMachine);
  gameThree.registerSoundStartUp(jingleStartUp);
  gameThree.registerSoundStart(jingleStart);
  gameThree.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME4
  gamepad.registerGame(&gameFour);
  gameFour.registerGameKey(gfStartGame, STARTGAMEID);
  gameFour.registerGameJoystick(&joystick);
  gameFour.registerSoundMachine(&soundMachine);
  gameFour.registerSoundStartUp(jingleStartUp);
  gameFour.registerSoundStart(jingleStart);
  gameFour.registerColorDotMatrix(&cdm);
  #endif
  #ifdef GAME5
  gamepad.registerGame(&gameFive);
  gameFive.registerGameKey(gfStartGame, STARTGAMEID);
  gameFive.registerGameJoystick(&joystick);
  gameFive.registerSoundMachine(&soundMachine);
  gameFive.registerSoundStartUp(jingleStartUp);
  gameFive.registerSoundStart(jingleStart);
  gameFive.registerColorDotMatrix(&cdm);
  #endif
  // Init
  #if (PROD == true)
  unitBinaryClock.setWorkMode(wmNone);
  #else
  unitBinaryClock.setWorkMode(wmObserveMemory);
  #endif
  unitBinaryClock.startUp();
  unitBinaryClock.clearInfo();
  #if (PROD == false)
  gamepad.setTestMode(true);
  #endif
  gamepad.initialize();
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {
  soundMachine.processingLoop();
  choosekeypad.processingLoop();
  if (gamepad.hasCurrentGame()) {
    gamekeypad.processingLoop();
    gamepad.processingLoop();
  } else {
    unitBinaryClock.processingLoop();
  }
}

void GameKeypadCallback(byte id) {
  gamepad.handleGameKeyEvent(id);
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void ChooseKeypadCallback(byte id) {
  switch (id) {
    case KEYCLOCKCOLOROFFID:
      if (!gamepad.hasCurrentGame()) {
        clockColorOff.red = random(0, 256);
        clockColorOff.green = random(0, 256);
        clockColorOff.blue = random(0, 256);
        unitBinaryClock.setColorOff(clockColorOff);
      } else {
        cdm.clear();
        gamepad.setNoCurrentGame();
      }
      break;
    case KEYCLOCKCOLORONID:
      if (!gamepad.hasCurrentGame()) {
        clockColorOn.red = random(0, 256);
        clockColorOn.green = random(0, 256);
        clockColorOn.blue = random(0, 256);
        unitBinaryClock.setColorOn(clockColorOn);
      } else {
        cdm.clear();
        gamepad.setNoCurrentGame();
      }
      break;
    case GAMEONEID:
    case GAMETWOID:
      gamepad.setCurrentGame(id);
      break;
    case TOGGLESOUNDPIN:
      gamepad.toggleDoPlaySound();
      break;
  }
  #if (PROD == false)
  observeMemory(0);
  #endif
}
