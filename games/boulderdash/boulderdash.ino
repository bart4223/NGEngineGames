#define PROD true //false, true
#define DOTMATRIX //OLED, DOTMATRIX

#include <NGCommon.h>
#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <NGSerialNotification.h>
#include <NGJingleHelloDude.h>
#include <NGJingleSuperMarioShort.h>
#include <NGColorDotMatrixGameBoulderdash.h>
#ifdef OLED
#include <NGColorOLED.h>
#include <NGSpriteHeart.h>
#include <NGSpriteBomb.h>
#include <NGSpriteRocky.h>
#include <NGSpriteDiamond.h>
#include <NGSpriteBoulder.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif

#define KEYDELAY      500
#define JOYSTICKDELAY 100

#define SOUNDPIN 44

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
NGSoundMachine soundMachine = NGSoundMachine(SOUNDPIN);
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, JOYSTICKPINX, JOYSTICKPINY, JOYSTICKPINFIRE);
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif
NGColorDotMatrixGameBoulderdash game = NGColorDotMatrixGameBoulderdash();

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
  int jingleSuperMario = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.initialize();
  // Game
  #if (PROD == false)
  game.setLogging(true);
  game.setTestMode(true);
  game.registerNotification(new NGSerialNotification());
  #endif
  game.registerGameKey(gfStartGame, STARTGAMEID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleSuperMario);
  game.registerSoundStart(jingleHelloDude);
  game.registerColorDotMatrix(&cdm);
  #ifdef OLED
  NGCustomSprite *sprite = new NGSpriteDiamond(&cdm, true);
  game.registerScoreSprite(sprite);
  game.registerLiveCounterSprite(new NGSpriteHeart(&cdm, true));
  //game.registerFuseSprite(new NGSpriteBomb(&cdm, true));
  game.registerSprite(GAMEBOULDERDASHCOLORINDEXROCKY, new NGSpriteRocky(&cdm));
  game.registerSprite(GAMEBOULDERDASHCOLORINDEXDIAMOND01, sprite);
  game.registerSprite(GAMEBOULDERDASHCOLORINDEXDIAMOND02, sprite);
  game.registerSprite(GAMEBOULDERDASHCOLORINDEXBOULDER, new NGSpriteBoulder(&cdm, true));
  #endif
  game.initialize();
  game.startUp();
  observeMemory(0);
}

void loop() {
  soundMachine.processingLoop();
  keypad.processingLoop();
  game.processingLoop();
}

void SimpleKeypadCallback(byte id) {
  game.handleKeyEvent(id);
  observeMemory(0);
}
