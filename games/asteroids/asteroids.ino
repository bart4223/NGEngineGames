#define PROD true //false, true
#define DOTMATRIX //OLED, DOTMATRIX

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NGColorDotMatrixGameAsteroids.h>
#ifdef OLED
#include <NGColorOLED.h>
#include <NGSpriteDiamond.h>
#include <NGSpriteBoulder.h>
#include <NGSpriteLaserbeam.h>
#include <NGSpriteNone.h>
#include <NGSpriteSpaceship.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define KEYDELAY      500
#define JOYSTICKDELAY 100

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

#define JOYSTICKTHRESHOLDUP       200
#define JOYSTICKTHRESHOLDDOWN     823
#define JOYSTICKTHRESHOLDLEFT     200
#define JOYSTICKTHRESHOLDRIGHT    823

#define STARTGAMEPIN 15
#define STARTGAMEID  42

NGSimpleKeypad keypad = NGSimpleKeypad();
NGSoundMachine soundMachine = NGSoundMachine();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGColorDotMatrixGameAsteroids game = NGColorDotMatrixGameAsteroids();

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
  #ifdef OLED
  cdm.setScale(8);
  #endif
  cdm.clear();
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
  #ifdef OLED
  game.setIntroShotDelay(50);
  game.registerSprite(GAMEASTEROIDSCOLORINDEXASTEROID, new NGSpriteBoulder(&cdm, true));
  //game.registerSprite(GAMEASTEROIDSCOLORINDEXLASERBEAM, new NGSpriteLaserbeam(&cdm, true));
  game.registerSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT01, new NGSpriteSpaceship(&cdm, true, -9, 0));
  game.registerSprite(GAMEASTEROIDSCOLORINDEXSPACECRAFT02, new NGSpriteNone(&cdm));
  //game.registerScoreSprite(new NGSpriteDiamond(&cdm, true));
  #endif
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
