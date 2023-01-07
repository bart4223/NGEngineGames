#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NG8x8RGBMatrixGameTetris.h>

#define KEYDELAY      500
#define JOYSTICKDELAY 200

#define JOYSTICKID       0
#define JOYSTICKPINX    A8
#define JOYSTICKPINY    A9
#define JOYSTICKPINFIRE 14

#define JOYSTICKTHRESHOLDUP       100
#define JOYSTICKTHRESHOLDDOWN     923
#define JOYSTICKTHRESHOLDLEFT     100
#define JOYSTICKTHRESHOLDRIGHT    923

#define STARTGAMEPIN 15
#define STARTGAMEID  42

NGSimpleKeypad keypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
NGColorDotMatrix cdm = NGColorDotMatrix();
NG8x8RGBMatrixGameTetris game = NG8x8RGBMatrixGameTetris();

void setup() {
  observeMemory(0);
  // Keypad
  keypad.registerCallback(&SimpleKeypadCallback);
  keypad.registerKey(STARTGAMEPIN, STARTGAMEID, KEYDELAY);
  keypad.initialize();
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
  // Game
  #if (PROD == false)
  game.setLogging(true);
  game.registerNotification(new NGSerialNotification());
  #endif
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleHelloDude);
  game.registerSoundStart(jingleHelloDude);
  game.registerColorDotMatrix(&cdm);
  game.initialize();
  observeMemory(0);
  game.startUp();
}

void loop() {
  keypad.processingLoop();
  game.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  game.handleKeyEvent(id);
  observeMemory(0);
}
