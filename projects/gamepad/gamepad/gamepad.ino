#define PROD false //false, true

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGJingleHelloDude.h>
#include <NGSerialNotification.h>
#include <NGGamePad.h>
#include <NG8x8RGBMatrixGameDot.h>

#define GAMEONEPIN      8
#define GAMEONEID       0x00
#define GAMETWOPIN      9
#define GAMETWOID       0x01
#define GAMETHREEPIN    10
#define GAMETHREEID     0x02
#define GAMEFOURPIN     11
#define GAMEFOURID      0x03
#define GAMEFIVEPIN     12
#define GAMEFIVEID      0x04

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
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
NGColorDotMatrix cdm = NGColorDotMatrix();
NGGamePad gamepad = NGGamePad();
NG8x8RGBMatrixGameDot gameOne = NG8x8RGBMatrixGameDot();

void setup() {
  observeMemory(0);
  // GamePad
  #if (PROD == false)
  gamepad.setLogging(true);
  gamepad.registerNotification(new NGSerialNotification());
  #endif
  // ChooseKeypad
  choosekeypad.registerCallback(&ChooseKeypadCallback);
  choosekeypad.registerKey(GAMEONEPIN, GAMEONEID, KEYDELAY);
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
  int jingleHelloDude = soundMachine.registerJingle(new NGJingleHelloDude());
  soundMachine.initialize();
  // Game "One"
  gamepad.registerGame(&gameOne);
  gameOne.registerGameKey(gfStartGame, STARTGAMEID);
  gameOne.registerGameJoystick(&joystick);
  gameOne.registerSoundMachine(&soundMachine);
  gameOne.registerSoundStartUp(jingleHelloDude);
  gameOne.registerSoundStart(jingleHelloDude);
  gameOne.registerColorDotMatrix(&cdm);
  // Init
  gamepad.initialize();
  observeMemory(0);
}

void loop() {
  choosekeypad.processingLoop();
  gamekeypad.processingLoop();
  gamepad.processingLoop();
}

void GameKeypadCallback(byte id) {
  gamepad.handleGameKeyEvent(id);
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void ChooseKeypadCallback(byte id) {
  gamepad.setCurrentGame(id);
  #if (PROD == false)
  observeMemory(0);
  #endif
}
