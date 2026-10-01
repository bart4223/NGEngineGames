#define PROD true //false, true

#define DOT

#include <NGEngineGames.h>
#include <NGSerialNotification.h>
#include <Visuals/NGTFTDisplay.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleAlarm.h>
#include <NGJingleSuperMarioShort.h>
#include <NGPaintableComponentEffectVoid.h>
#include <NGSoundMachineEffect.h>

#ifdef DOT
#include <Sprites/NGSpriteDiamond.h>
#include <Sprites/NGSpriteRocky.h>
#endif

#define _GAMEMACHINE  "GameDude"
#define GAMEMACHINE   (char*)_GAMEMACHINE

#define TFTVERTICALSWITCH 42

#define KEYSELECTPIN  12
#define KEYSELECTID   42
#define KEYSTARTPIN   11
#define KEYSTARTID    43
#define KEYAPIN        6
#define KEYAID        44
#define KEYBPIN        7
#define KEYBID        45
#define KEYUPPIN       3
#define KEYUPID       46
#define KEYDOWNPIN     2
#define KEYDOWNID     47
#define KEYLEFTPIN     4
#define KEYLEFTID     48
#define KEYRIGHTPIN    5
#define KEYRIGHTID    49
#define KEYDELAY      500

#define THRESHOLDUP       100
#define THRESHOLDDOWN     923
#define THRESHOLDLEFT     100
#define THRESHOLDRIGHT    923
#define JOYSTICKID          0
#define JOYSTICKDELAY      50

#define GAMEMACHINESTARTCOLOR COLOR_BLUE_C64_LOW

NGTFTDisplay display = NGTFTDisplay();

NGZX81Font *fontSplash = new NGZX81Font();

#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGSoundMachine soundMachine = NGSoundMachine();
NGSimpleKeypad skpMain = NGSimpleKeypad();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, KEYLEFTPIN, KEYRIGHTPIN, KEYDOWNPIN, KEYUPPIN, KEYAPIN);

#ifdef DOT
#define DISPLAYSCALE 8
#define GAMEMACHINESTARTCOLORDONE COLOR_GRAY
#define GAMEMACHINESCORECOLOROFF COLOR_DARKGRAY
#define GAMEMACHINESCORECOLORON COLOR_GOLD
#define GAMEMACHINEIDLETEXTCOLOR COLOR_DARKBLUE
NGColorDotMatrixGameDot game = NGColorDotMatrixGameDot();
#endif

NGColorDotMatrixEffectRetroRibbons *effectOne = new NGColorDotMatrixEffectRetroRibbons(&display);
NGSoundMachineEffect *effectTwo = new NGSoundMachineEffect(&soundMachine);
NGColorDotMatrixEffectText *effectThree = new NGColorDotMatrixEffectText(&display, COLOR_WHITE, COLOR_TRANSPARENT, fontSplash, setkFull);
NGColorDotMatrixEffectGameIdle *effectFinal = new NGColorDotMatrixEffectGameIdle(&display, &game);

#if (PROD == false)
NGSplash splash = NGSplash(&serialNotification);
#else
NGSplash splash = NGSplash();
#endif

NGGameMachineUnitControl unitGameMachine = NGGameMachineUnitControl(GAMEMACHINE, &game);

byte jingleBootID;
byte jingleBeepID;
byte jingleAlarmID;
byte jingleStartup;

void setup() {
  #if (PROD == false)
  observeMemory(0);
  #endif
  initGlobalRandomSeedWithAnalogInput(A15);
  // Display
  display.initialize();
  if (IsSwitchOn(TFTVERTICALSWITCH)) {
    display.setDisplayDirection(tddVertical);
  } else {
    display.setDisplayDirection(tddHorizontal);
  }
  display.setBackground(GAMEMACHINESTARTCOLOR);
  display.clear();
  display.setBackground(GAMEMACHINESTARTCOLORDONE);
  display.setScale(DISPLAYSCALE);
  #if (PROD == false)
  char log[100];
  sprintf(log, "TFT-Width: %d, TFT-Height %d", display.getWidth(), display.getHeight());
  Serial.println(log);
  #endif
  // Sound
  jingleBootID = soundMachine.registerJingle(new NGJingleBoot);
  jingleBeepID = soundMachine.registerJingle(new NGJingleBeep);
  jingleAlarmID = soundMachine.registerJingle(new NGJingleAlarm);
  jingleStartup = soundMachine.registerJingle(new NGJingleSuperMarioShort());
  soundMachine.setConcurrently(true);
  soundMachine.initialize();
  soundMachine.activate();
  // Joystick
  joystick.registerAction(jamMappingInvers, jaX, jtkLess, THRESHOLDLEFT, JOYSTICKDELAY, jmLeft);
  joystick.registerAction(jamMapping, jaX, jtkGreater, THRESHOLDRIGHT, JOYSTICKDELAY, jmRight);
  joystick.registerAction(jamMappingInvers, jaY, jtkLess, THRESHOLDUP, JOYSTICKDELAY, jmUp);
  joystick.registerAction(jamMapping, jaY, jtkGreater, THRESHOLDDOWN, JOYSTICKDELAY, jmDown);
  joystick.registerAction(KEYAPIN, jamTriggerLOW, JOYSTICKDELAY, jmFire);
  joystick.initialize();
  // Main Keypad
  skpMain.registerCallback(&KeypadCallback);
  skpMain.registerKey(KEYSELECTPIN, KEYSELECTID, KEYDELAY);
  skpMain.registerKey(KEYSTARTPIN, KEYSTARTID, KEYDELAY);
  skpMain.registerKey(KEYAPIN, KEYAID, KEYDELAY);
  skpMain.registerKey(KEYBPIN, KEYBID, KEYDELAY);
  skpMain.initialize();
  // Splash
  splash.registerPaintableComponent(&display);
  splash.registerEffect(effectOne, 500, 2000);
  #if (PROD == true)
  effectTwo->playJingle(jingleBootID);
  splash.registerEffect(effectTwo, 0, 1500);
  #endif
  effectThree->setPosition((display.getWidth() - strlen(GAMEMACHINE)) / 2, display.getHeight() / 2 + 10);
  effectThree->setText(GAMEMACHINE);
  effectFinal->setFont(fontSplash);
  effectFinal->setTextColor(GAMEMACHINEIDLETEXTCOLOR);
  effectFinal->setTextSecondary("\xA9 by NG 2026");
  splash.registerEffect(effectThree, 2500, 1500);
  splash.registerEffect(effectFinal, 4200, 10);
  // GameMachine
  setGlobalUnit(&unitGameMachine);
  unitGameMachine.registerSplash(&splash);
  #if (PROD == false)
  unitGameMachine.setLogging(true);
  #else
  unitGameMachine.setLogging(false);
  #endif
  unitGameMachine.registerKeypad(&skpMain);
  unitGameMachine.initialize();
  game.setGameMode(gmBig);
  // Game "Dot"
  #ifdef DOT
  game.registerGameKey(gfStartGame, KEYSTARTID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&display);
  game.registerDotSprite(new NGSpriteDiamond(&display, true));
  game.registerPlayerSprite(new NGSpriteRocky(&display, true));
  game.setScoreColorOff(GAMEMACHINESCORECOLOROFF);
  game.setScoreColorOn(GAMEMACHINESCORECOLORON);
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
  #if (PROD == false)
  observeMemory(0);
  #endif
}

void loop() {
  soundMachine.processingLoop();
  unitGameMachine.processingLoop();
}

void KeypadCallback(byte id) {
  switch(id) {
    case KEYSTARTID:
      #if (PROD == false)
      Serial.println("Press START");
      #endif
      unitGameMachine.startGame();
      break;
  }
}