#define PROD true //false, true
#define UNO
#define DOTMATRIX //OLED, DOTMATRIX

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGColorDotMatrixGameDot.h>
#ifdef OLED
#include <NGColorOLED.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define KEYDELAY      500
#define JOYSTICKDELAY 100

#define JOYSTICKID       0
#ifdef UNO
#define JOYSTICKPINX    A1
#else
#define JOYSTICKPINX    A8
#endif
#ifdef UNO
#define JOYSTICKPINY    A2
#else
#define JOYSTICKPINY    A9
#endif
#define JOYSTICKPINFIRE 14

#define JOYSTICKTHRESHOLDUP       100
#define JOYSTICKTHRESHOLDDOWN     923
#define JOYSTICKTHRESHOLDLEFT     100
#define JOYSTICKTHRESHOLDRIGHT    923

#define STARTGAMEPIN 15
#define STARTGAMEID  42

NGSimpleKeypad keypad = NGSimpleKeypad();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGColorDotMatrixGameDot game = NGColorDotMatrixGameDot();

void setup() {
  observeMemory(0);
  #if (PROD == false)
  game.setLogging(true);
  game.registerNotification(new NGSerialNotification());
  #endif
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
  #ifdef OLED
  cdm.setScale(5);
  #endif
  cdm.clear();
  // Game
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
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
