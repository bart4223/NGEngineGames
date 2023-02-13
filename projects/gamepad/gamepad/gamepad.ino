#define PROD true //false, true
#define GAMES3

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGJingleHelloDude.h>
#include <NGJingleSuperMarioShort.h>
#include <NGJingleGorilla.h>
#include <NGSerialNotification.h>
#include <NGBinaryClockUnitControl.h>
#include <NGGamePad.h>
#include <NG8x8RGBMatrixGameDot.h>
#include <NG8x8RGBMatrixGameSnake.h>
#include <NG8x8RGBMatrixGameAsteroids.h>
#include <NG8x8RGBMatrixGameTetris.h>
#include <NG8x8RGBMatrixGameBoulderdash.h>

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
NGColorDotMatrix cdm = NGColorDotMatrix();
NGBinaryClockUnitControl unitBinaryClock = NGBinaryClockUnitControl(BINARYCLOCK, &cdm);
NGGamePad gamepad = NGGamePad();
#ifdef GAMES1
NG8x8RGBMatrixGameDot gameOne = NG8x8RGBMatrixGameDot();
NG8x8RGBMatrixGameSnake gameTwo = NG8x8RGBMatrixGameSnake();
#endif
#ifdef GAMES2
NG8x8RGBMatrixGameAsteroids gameOne = NG8x8RGBMatrixGameAsteroids();
NG8x8RGBMatrixGameTetris gameTwo = NG8x8RGBMatrixGameTetris();
#endif
#ifdef GAMES3
NG8x8RGBMatrixGameTetris gameOne = NG8x8RGBMatrixGameTetris();
NG8x8RGBMatrixGameBoulderdash gameTwo = NG8x8RGBMatrixGameBoulderdash();
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
  // ColorDotMatrix
  cdm.initialize();
  // Sound
  int jingleStartUpOne = soundMachine.registerJingle(new NGJingleGorilla());
  int jingleStartUpTwo = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  int jingleStart = soundMachine.registerJingle(new NGJingleHelloDude());
  soundMachine.initialize();
  // Game "One"
  gamepad.registerGame(&gameOne);
  gameOne.registerGameKey(gfStartGame, STARTGAMEID);
  gameOne.registerGameJoystick(&joystick);
  gameOne.registerSoundMachine(&soundMachine);
  gameOne.registerSoundStartUp(jingleStartUpOne);
  gameOne.registerSoundStart(jingleStart);
  gameOne.registerColorDotMatrix(&cdm);
  // Game "Two"
  gamepad.registerGame(&gameTwo);
  gameTwo.registerGameKey(gfStartGame, STARTGAMEID);
  gameTwo.registerGameJoystick(&joystick);
  gameTwo.registerSoundMachine(&soundMachine);
  gameTwo.registerSoundStartUp(jingleStartUpTwo);
  gameTwo.registerSoundStart(jingleStart);
  gameTwo.registerColorDotMatrix(&cdm);
  // Init
  #if (PROD == true)
  unitBinaryClock.setWorkMode(wmNone);
  #else
  unitBinaryClock.setWorkMode(wmObserveMemory);
  #endif
  unitBinaryClock.startUp();
  unitBinaryClock.clearInfo();
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
