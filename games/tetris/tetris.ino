#define PROD true //false, true
#define DOTMATRIX //OLED, DOTMATRIX

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NGJingleSuperMarioShort.h>
#include <NGColorDotMatrixGameTetris.h>
#ifdef OLED
#include <NGColorOLED.h>
#include <NGSpriteDiamond.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define SOUNDPIN 44

#define KEYDELAY      500
#define JOYSTICKDELAY 200

#define JOYSTICKID       0
#ifdef NG_PLATFORM_UNO
#define JOYSTICKPINX    A1
#else
#define JOYSTICKPINX    A8
#endif
#ifdef NG_PLATFORM_UNO
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
#define SCALEDOWNPIN 17
#define SCALEDOWNID  43
#define SCALEUPPIN   16
#define SCALEUPID    44

NGSimpleKeypad keypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine(SOUNDPIN);
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGColorDotMatrixGameTetris game = NGColorDotMatrixGameTetris();

void setup() {
  observeMemory(0);
  // Keypad
  keypad.registerCallback(&SimpleKeypadCallback);
  keypad.registerKey(STARTGAMEPIN, STARTGAMEID, KEYDELAY);
  keypad.registerKey(SCALEDOWNPIN, SCALEDOWNID, KEYDELAY);
  keypad.registerKey(SCALEUPPIN, SCALEUPID, KEYDELAY);
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
  cdm.setScale(8);
  #endif
  cdm.clear();
  // Sound
  int jingleHelloDude = soundMachine.registerJingle(new NGJingleHelloDude());
  int jingleSuperMario = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.initialize();
  // Game
  #if (PROD == false)
  game.setLogging(true);
  game.registerNotification(new NGSerialNotification());
  #endif
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleSuperMario);
  game.registerSoundStart(jingleHelloDude);
  game.registerColorDotMatrix(&cdm);
  #ifdef OLED
  game.registerScoreSprite(new NGSpriteDiamond(&cdm, true));
  #endif
  game.initialize();
  observeMemory(0);
  game.startUp();
}

void loop() {
  soundMachine.processingLoop();
  keypad.processingLoop();
  game.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  int scale;
  switch(id) {
    case SCALEDOWNID:
      scale = cdm.getScale();
      if (scale > 1) {
        cdm.setScale(scale - 1);
        cdm.clear();
      }
      break;
    case SCALEUPID:
      scale = cdm.getScale();
      cdm.setScale(scale + 1);
      cdm.clear();
      break;
    default:
      game.handleKeyEvent(id);
      break;
  }
  observeMemory(0);
}
