#define PROD false //false, true

#define DOT

#include <NGEngineGames.h>
#include <NGSerialNotification.h>
#include <Visuals/NGTFTDisplay.h>
#include <NGJingleBoot.h>
#include <NGJingleBeep.h>
#include <NGJingleAlarm.h>
#include <NGJingleSuperMarioShort.h>

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
#define KEYUPPIN       2
#define KEYUPID       46
#define KEYDOWNPIN     3
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

NGTFTDisplay tft = NGTFTDisplay();
#if (PROD == false)
NGSerialNotification serialNotification = NGSerialNotification();
#endif
NGSoundMachine soundMachine = NGSoundMachine();
NGSimpleKeypad skpMain = NGSimpleKeypad();
NGJoystickControl joystick = NGJoystickControl(JOYSTICKID, KEYLEFTPIN, KEYRIGHTPIN, KEYDOWNPIN, KEYUPPIN, KEYAPIN);

#ifdef DOT
NGColorDotMatrixGameDot game = NGColorDotMatrixGameDot();
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
  // TFT
  tft.initialize();
  if (IsSwitchOn(TFTVERTICALSWITCH)) {
    tft.setDisplayDirection(tddVertical);
  } else {
    tft.setDisplayDirection(tddHorizontal);
  }
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
  // GameMachine
  setGlobalUnit(&unitGameMachine);
  #if (PROD == false)
  unitGameMachine.setLogging(true);
  #else
  unitGameMachine.setLogging(false);
  #endif
  unitGameMachine.registerKeypad(&skpMain);
  unitGameMachine.initialize();
  // Game "Dot"
  #ifdef DOT
  game.registerGameKey(gfStartGame, KEYSTARTID);
  game.registerGameJoystick(&joystick);
  game.registerSoundMachine(&soundMachine);
  game.registerSoundStartUp(jingleStartup);
  game.registerColorDotMatrix(&tft);
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